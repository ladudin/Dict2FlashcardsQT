#include "AudiosWidget.hpp"
#include "ui_AudiosWidget.h"
#include <QPushButton>
#include "Player.hpp"


AudiosWidget::AudiosWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudiosWidget)
{
    ui->setupUi(this);
    gridLayout = new QGridLayout;
    gridLayout->setAlignment(Qt::AlignTop);
    QWidget *audiosListWidget = new QWidget;
    audiosListWidget->setLayout(gridLayout);
    ui->scrollArea->setWidget(audiosListWidget);
}

AudiosWidget::~AudiosWidget()
{
    delete ui;
}

void AudiosWidget::addAudio(SourceWithAdditionalInfo audio, bool isLocal, bool isChosen) {
    // SPDLOG_INFO("Adding sentence with text: {}", sentence.toStdString());

    QPushButton *pushButton = new QPushButton;
    pushButton->setCheckable(true);
    pushButton->setStyleSheet("QPushButton:checked { background-color: green; }");
    pushButton->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);

    Player *audioPlayer = new Player;
    audioPlayer->set(audio, isLocal);

    if (isChosen) {
        pushButton->setChecked(true);
    }
    
    audioPlayer->setMaximumHeight(100);
    pushButton->setMaximumHeight(40);
    pushButton->setMaximumWidth(40);

    int new_row = gridLayout->count() / gridLayout->columnCount();

    gridLayout->addWidget(pushButton, new_row, 0);
    gridLayout->addWidget(audioPlayer, new_row, 1);

    // SPDLOG_INFO("Sentence added. Row count =  {}", gridLayout->count() / gridLayout->columnCount());
}
