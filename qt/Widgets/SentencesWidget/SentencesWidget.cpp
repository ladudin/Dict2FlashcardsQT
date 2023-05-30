#include "SentencesWidget.hpp"
#include "spdlog/fmt/bundled/format.h"
#include "spdlog/spdlog.h"
#include "ui_SentencesWidget.h"
#include <QTextEdit>
#include <QPushButton>
#include <QLayoutItem>
#include <qdebug.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qtextedit.h>
#include <qwidget.h>
#include <qwindowdefs.h>
#include <QDebug>

SentencesWidget::SentencesWidget(std::unique_ptr<ISentencePluginWrapper> sentencePlugin,
                            QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SentencesWidget)
{
    ui->setupUi(this);
    sentencePlugin_ = std::move(sentencePlugin);
    sentencePlugin_->init("sentences");
    gridLayout = new QGridLayout;
    gridLayout->setAlignment(Qt::AlignTop);
    QWidget *sentencesListWidget = new QWidget;
    sentencesListWidget->setObjectName("ListWidget");
    sentencesListWidget->setLayout(gridLayout);
    ui->scrollArea->setWidget(sentencesListWidget);
    load("go");
}

SentencesWidget::~SentencesWidget()
{
    delete ui;
}

void SentencesWidget::addSentence(QString sentence, bool is_chosen)
{
    SPDLOG_INFO("Adding sentence with text: {}", sentence.toStdString());
    
    QTextEdit *textEdit = new QTextEdit;
    textEdit->setPlaceholderText("Sentence");
    textEdit->setText(sentence);

    QPushButton *pushButton = new QPushButton;
    pushButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    
    textEdit->setMaximumHeight(100);
    pushButton->setMaximumHeight(100);

    int new_row = gridLayout->count() / gridLayout->columnCount();

    gridLayout->addWidget(textEdit, new_row, 0);
    gridLayout->addWidget(pushButton, new_row, 1);

    SPDLOG_INFO("Sentence added. Row count =  {}", gridLayout->count() / gridLayout->columnCount());
}

void SentencesWidget::load(QString word, int batch_size) {
    SPDLOG_INFO("Start loading sentences");
    auto [sentences, error] = sentencePlugin_->get(word.toStdString(), batch_size, false);

    for (const std::string& sentence: sentences) {
        addSentence(QString::fromStdString(sentence));
    }

    SPDLOG_INFO("Loaded {} sentences", sentences.size());
    SPDLOG_INFO("Message from sentencePlugin: {}", error);
}

void SentencesWidget::clear() {
    SPDLOG_INFO("Clear start. Row count = {}", gridLayout->count() / gridLayout->columnCount());
    QLayoutItem *item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        QWidget *widget = item->widget();
        gridLayout->removeItem(item);
        widget->deleteLater();
        delete item;
    }
    SPDLOG_INFO("Clear end. Row count = {}", gridLayout->count() / gridLayout->columnCount());
}