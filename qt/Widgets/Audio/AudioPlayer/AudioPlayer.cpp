#include "AudioPlayer.hpp"
#include "ui_AudioPlayer.h"
#include <QDial>
#include <QStyle>
#include <QString>
#include <QFileDialog>
#include <QTime>
#include <QTextEdit>

MyAudioPlayer::MyAudioPlayer(QWidget *parent):
    QWidget(parent),
    ui(new Ui::MyAudioPlayer)
{
    m_infoEdit = new QTextEdit;
    m_infoEdit->setPlaceholderText("Audio additional info");
    m_infoEdit->setEnabled(false);

    m_pcmdPlay = new QPushButton;
    m_pcmdStop = new QPushButton;
    m_psldPosition = new QSlider;
    m_plblCurrent = new QLabel(msecsToString(0));
    m_plblRemain = new QLabel(msecsToString(0));
    m_pmp = new QMediaPlayer;

    m_pcmdPlay->setEnabled(false);
    m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));

    m_pcmdStop->setEnabled(false);
    m_pcmdStop->setIcon(style()->standardIcon(QStyle::SP_MediaStop));

    m_psldPosition->setRange(0, 0);
    m_psldPosition->setOrientation(Qt::Horizontal);

    connect(m_pcmdPlay, SIGNAL(clicked()), SLOT(slotPlay()));
    connect(m_pcmdStop, SIGNAL(clicked()), m_pmp, SLOT(stop()));
    connect(m_pmp, SIGNAL(positionChanged(qint64)), SLOT(slotSetSliderPosition(qint64)));
    connect(m_pmp, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(m_pmp, SIGNAL(stateChanged(QMediaPlayer::State)),
            SLOT(slotStatusChanged(QMediaPlayer::State)));

    QHBoxLayout* phbxPlayControls = new QHBoxLayout;
    phbxPlayControls->addWidget(m_pcmdPlay);
    phbxPlayControls->addWidget(m_infoEdit);

    QHBoxLayout* phbxTimeControls = new QHBoxLayout;
    phbxTimeControls->addWidget(m_plblCurrent);
    phbxTimeControls->addWidget(m_psldPosition);
    phbxTimeControls->addWidget(m_plblRemain);

    m_pvbxMainLayout = new QVBoxLayout;
    m_pvbxMainLayout->addLayout(phbxPlayControls);
    m_pvbxMainLayout->addLayout(phbxTimeControls);

    setLayout(m_pvbxMainLayout);
}

MyAudioPlayer::~MyAudioPlayer()
{
    delete ui;
}

void MyAudioPlayer::set(SourceWithAdditionalInfo audio, bool isLocal)
{
    m_audio = audio;
    m_isLocal = isLocal;
    m_infoEdit->setText(QString::fromStdString(audio.info));
    slotOpen();
}

void MyAudioPlayer::slotOpen()
{
    QUrl url;
    if (m_isLocal) {
        url = QUrl::fromLocalFile(QString::fromStdString(m_audio.src));
    }
    else {
        url = QUrl(QString::fromStdString(m_audio.src));
    }
    if (url.isValid()) {
        m_pmp->setMedia(url);
        m_pcmdPlay->setEnabled(true);
        m_pcmdStop->setEnabled(true);
    }
}

void MyAudioPlayer::slotPlay()
{
    switch (m_pmp->state()) {
    case QMediaPlayer::PlayingState:
        m_pmp->pause();
        break;
    default:
        m_pmp->play();
        break;
    }
}

void MyAudioPlayer::slotStatusChanged(QMediaPlayer::State state)
{
    switch (state) {
    case QMediaPlayer::PlayingState:
        m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        break;
    default:
        m_pcmdPlay->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    }
}

void MyAudioPlayer::slotSetMediaPosition(int n)
{
    m_pmp->setPosition(n);
}

QString MyAudioPlayer::msecsToString(qint64 n)
{
    int nHours = (n / (60 * 60 * 1000));
    int nMinutes = ((n % (60 * 60 * 1000)) / (60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);

    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm::ss");
}

void MyAudioPlayer::slotSetDuration(qint64 n)
{
    m_psldPosition->setRange(0, n);
    m_plblCurrent->setText(msecsToString(0));
    m_plblRemain->setText(msecsToString(n));
}

void MyAudioPlayer::slotSetSliderPosition(qint64 n)
{
    m_psldPosition->setValue(n);

    m_plblCurrent->setText(msecsToString(n));
    int nDuration = m_psldPosition->maximum();
    m_plblRemain->setText(msecsToString(nDuration - n));
}
