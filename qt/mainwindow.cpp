#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deck_model.h"
#include "deckmock.h"
#include <memory>
#include <QBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    auto deck = std::make_shared<DeckMock>();
    examples_model = new ExamplesModel;
    ui->examplesView->setModel(examples_model);
    audio_model = new AudioModel;
    ui->audioView->setModel(audio_model);
    images_model = new ImagesModel;
    ui->ImagesView->setModel(images_model);
    deck_model = new DeckModel(deck, ui->deckView);
    ui->deckView->setModel(deck_model);
    connect(ui->searchLine, SIGNAL(returnPressed()), this, SLOT(onSearchReturned()));
    connect(ui->deckView, SIGNAL(clicked(QModelIndex)), this, SLOT(setCurrentIndex(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onSearchReturned()
{
    qDebug() << deck_model->rowCount();
    QString word = ui->searchLine->text();
    if (word == "")
    {
        return;
    }
    int int_idx = deck_model->indexOfWord(word);
    if (int_idx == -1)
    {
        deck_model->load(ui->searchLine->text());
        QModelIndex qm_idx = deck_model->index(deck_model->rowCount() - 1);
        ui->deckView->setCurrentIndex(qm_idx);
        emit ui->deckView->clicked(qm_idx);
        return;
    }
    QModelIndex qm_idx = deck_model->index(int_idx);
    ui->deckView->setCurrentIndex(qm_idx);
    emit ui->deckView->clicked(qm_idx);
}

void MainWindow::updateCardFields()
{
    QVariant qvar = deck_model->data(current_index, DeckModel::CardRole);
    Card* card = qvar.value<Card*>();
    updateWord(card);
    updateDefinition(card);
    updateExamples(card);
}

void MainWindow::updateWord(Card *card)
{
    if (!card)
    {
        return;
    }
    ui->wordLine->setText(QString::fromStdString(card->word));
}

void MainWindow::updateDefinition(Card *card)
{
    if (!card)
    {
        return;
    }
    ui->definitionEdit->setText(QString::fromStdString(card->definition));
}

void MainWindow::updateTags(Card *)
{

}

void MainWindow::updateExamples(Card *card)
{
    examples_model->setExamples(card->exaples);
}

void MainWindow::updateAudio(Card *card)
{
    audio_model->setAudio(card->audio_links);
}

void MainWindow::updateImages(Card *card)
{
    images_model->setImages(card->image_links);
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
    deck_model->next(current_index);
    updateCardFields();
}

void MainWindow::onPrevClicked()
{
    if (!current_index.isValid()) {
        return;
    }
    deck_model->prev(current_index);
    updateCardFields();
}

