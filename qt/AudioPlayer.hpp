#ifndef AUDIOPLAYER_HPP
#define AUDIOPLAYER_HPP

#include <QWidget>
#include <string>
#include <QMediaPlayer>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include "Media.hpp"

namespace Ui {
class AudioPlayer;
}

class AudioPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit AudioPlayer(QWidget *parent = nullptr);
    ~AudioPlayer();

public slots:
    void set(SourceWithAdditionalInfo audio, bool isLocal);

private:
    Ui::AudioPlayer *ui;
    SourceWithAdditionalInfo m_audio;
    bool m_isLocal;
    QPushButton* m_pcmdPlay;
    QPushButton* m_pcmdStop;
    QSlider* m_psldPosition;
    QLabel* m_plblCurrent;
    QLabel* m_plblRemain;
    QTextEdit* m_infoEdit;

    QString msecsToString(qint64 n);

protected:
    QMediaPlayer* m_pmp;
    QVBoxLayout* m_pvbxMainLayout;

private slots:
    void slotOpen();
    void slotPlay();
    void slotSetSliderPosition(qint64);
    void slotSetMediaPosition(int);
    void slotSetDuration(qint64);
    void slotStatusChanged(QMediaPlayer::State);
};

#endif // AUDIOPLAYER_HPP
