#include "AudiosWidget.hpp"
#include "Media.h"
#include "ui_AudiosWidget.h"
#include <QPushButton>
#include <qmediaplayer.h>
#include "Player.hpp"


AudiosWidget::AudiosWidget(std::unique_ptr<IAudioPluginWrapper> audioPlugin,
                        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudiosWidget)
{
    ui->setupUi(this);
    audioPlugin_ = std::move(audioPlugin);
    audioPlugin_->init("audios");
    gridLayout = new QGridLayout;
    gridLayout->setAlignment(Qt::AlignTop);
    QWidget *audiosListWidget = new QWidget;
    audiosListWidget->setLayout(gridLayout);
    ui->scrollArea->setWidget(audiosListWidget);
    mediaPlayer = new QMediaPlayer(this);
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

    Player *audioPlayer = new Player(mediaPlayer);
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

void AudiosWidget::load(QString word, int batch_size) {
    auto [audios, error] = audioPlugin_->get(word.toStdString(), batch_size, false);

    for (SourceWithAdditionalInfo localAudio: audios.local) {
        addAudio(localAudio, true);
    }
    for (SourceWithAdditionalInfo webAudio: audios.web) {
    addAudio(webAudio, false);
    }
}
