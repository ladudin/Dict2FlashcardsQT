#include "Player.hpp"
#include "ui_Player.h"
#include <qdatetime.h>
#include <qmediaplayer.h>
#include <qnetworkreply.h>
#include <qurl.h>
#include <QStyle>
#include <QTimer>
#include <string>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <sys/socket.h>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    audioPlayer = new QMediaPlayer(this);
    ui->playButton->setEnabled(false);
    ui->playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(audioPlayer, &QMediaPlayer::stateChanged, 
            this, &Player::onStateChanged);
    connect(audioPlayer, &QMediaPlayer::mediaStatusChanged, 
            this, &Player::onStatusChanged);
}

Player::~Player()
{
    delete ui;
}

void Player::download(QUrl url) {
}

void Player::onFinished() {
    qDebug() << "here";
    QByteArray bytes = reply->readAll();
    qDebug() << bytes.size();
}

void Player::set(SourceWithAdditionalInfo audio, bool isLocal) {
    qDebug() << "here";
    if (isLocal) {
        audioPlayer->setMedia(QUrl::fromLocalFile(QString::fromStdString(audio.src)));
        return;
    }
    audioPlayer->setMedia(QUrl(QString::fromStdString(audio.src)));
    ui->infoEdit->setText(QString::fromStdString(audio.info));
}

void Player::onStateChanged(QMediaPlayer::State state) {
    // if (state == QMediaPlayer::StoppedState) {
    //     ui->playButton->setEnabled(true);
    // }
}

void Player::onStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::LoadedMedia) {
        ui->playButton->setEnabled(true);
    }
}

void Player::onPlayClicked() {
    audioPlayer->play();
    ui->playButton->setEnabled(false);
    // QTimer::singleShot(maxPlayDuration, audioPlayer, SLOT(stop()));
}
