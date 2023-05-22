#include "mainwindow.h"
#include "AudioWidget.hpp"
#include "Card.h"
#include "ExamplesWidget.hpp"
#include "IRequestable.h"
#include "IWordPluginWrapper.h"
#include "ImagesWidget.hpp"
#include "ui_mainwindow.h"
#include "deck_model.h"
#include "Deck.hpp"
#include "WordPluginWrapper.h"
#include "FormatProcessorPluginWrapper.h"
#include "ServerConnection.h"
#include <filesystem>
#include <memory>
#include <QBoxLayout>
#include <iostream>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connection = std::make_shared<ServerConnection>(8888);
    std::unique_ptr<IWordPluginWrapper> wordPlugin = std::make_unique<WordPluginWrapper>(connection);
    wordPlugin->init("definitions");
    std::unique_ptr<IDeck> deck = std::make_unique<Deck>(std::move(wordPlugin));
    std::cout << "deck: " << int(deck != nullptr) << std::endl;
    deckModel = new DeckModel(std::move(deck), this);
    examplesWidget = new ExamplesWidget;
    ui->examplesTab->layout()->addWidget(examplesWidget);
    audioWidget = new AudioWidget;
    ui->audioTab->layout()->addWidget(audioWidget);
    imagesWidget = new IMagesWidget;
    ui->imagesTab->layout()->addWidget(imagesWidget);
    ui->deckView->setModel(deckModel);
    std::cout << "affadfadsf " << (deckModel->deck_ != nullptr) << std::endl;
    std::cout << ui->deckView << " " << deckModel->parent() << std::endl;
    connect(ui->searchLine, SIGNAL(returnPressed()), this, SLOT(onSearchReturned()));
    connect(ui->deckView, SIGNAL(clicked(QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSearchReturned()
{
    QString word = ui->searchLine->text();
    if (word == "")
    {
        return;
    }
    int int_idx = deckModel->indexOfWord(word);
    if (int_idx == -1)
    {
        deckModel->load(ui->searchLine->text(), ui->filterEdit->toPlainText());
        QModelIndex qm_idx = deckModel->index(deckModel->rowCount() - 1);
        ui->deckView->setCurrentIndex(qm_idx);
        emit ui->deckView->clicked(qm_idx);
        return;
    }
    QModelIndex qm_idx = deckModel->index(int_idx);
    ui->deckView->setCurrentIndex(qm_idx);
    emit ui->deckView->clicked(qm_idx);
}

void MainWindow::updateCardFields()
{
    ui->tabWidget->setCurrentIndex(0);
    QVariant qvar = deckModel->data(current_index, DeckModel::CardRole);
    void* void_card = qvar.value<void*>();
    const Card* card = static_cast<const Card*>(void_card);
    updateWord(card);
    updateDefinition(card);
    updateExamples(card);
    updateAudio(card);
    updateImages(card);
}

void MainWindow::updateWord(const Card *card)
{
    if (!card)
    {
        return;
    }
    ui->wordLine->setText(QString::fromStdString(card->word));
}

void MainWindow::updateDefinition(const Card *card)
{
    if (!card)
    {
        return;
    }
    ui->definitionEdit->setText(QString::fromStdString(card->definition));
}

void MainWindow::updateTags(const Card *)
{

}

void MainWindow::updateExamples(const Card *card)
{
    if (!card) {
        return;
    }
    examplesWidget->set(&card->examples);
}

void MainWindow::updateAudio(const Card *card)
{
    if (!card) {
        return;
    }
    std::cout << card->audios.web[0].src << std::endl;
    audioWidget->set(card->audios);
}

void MainWindow::updateImages(const Card *card)
{
    if (!card) {
        return;
    }
    imagesWidget->set(card->images);
}

void MainWindow::setCurrentIndex(QModelIndex index)
{
    current_index = index;
    updateCardFields();
}

void MainWindow::onNextClicked()
{
    if (!current_index.isValid()) {
        return;
    }
    deckModel->next(current_index);
    updateCardFields();
}

void MainWindow::onPrevClicked()
{
    if (!current_index.isValid()) {
        return;
    }
    deckModel->prev(current_index);
    updateCardFields();
}

void MainWindow::onAddClicked() {
    Card card;
    card.word = ui->wordLine->text().toStdString();
    card.definition = ui->definitionEdit->toPlainText().toStdString();
    card.examples = examplesWidget->extract();
    card.audios = audioWidget->extract();
    card.images = imagesWidget->extract();
    savedDeck.push_back(card);
    onNextClicked();
}

void MainWindow::save() {
    std::string relative_path = "./savedDeck.json";
    auto absolute_path = std::filesystem::absolute(relative_path).string();
    save_cards(savedDeck, absolute_path);
    FormatProcessorPluginWrapper savingPlugin(connection);
    savingPlugin.init("processor");
    savingPlugin.save(absolute_path);
}