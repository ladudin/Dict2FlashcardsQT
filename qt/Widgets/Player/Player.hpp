#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <QWidget>
#include <QMediaPlayer>
#include <qmediaplayer.h>
#include <qnetworkreply.h>
#include <qurl.h>
#include "Card.h"
#include "Media.h"

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);
    ~Player();
    void download(QUrl url);

public slots:
    void set(SourceWithAdditionalInfo audio, bool isLocal);
    void onStateChanged(QMediaPlayer::State state);
    void onStatusChanged(QMediaPlayer::MediaStatus status);
    void onPlayClicked();
    void onFinished();

private:
    Ui::Player *ui;
    QMediaPlayer *audioPlayer;
    QNetworkReply *reply;
    const int maxPlayDuration = 5000;
};

#endif // PLAYER_HPP
