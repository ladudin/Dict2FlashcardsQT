#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QWidget>
#include <QGridLayout>
#include <memory>
#include <qgridlayout.h>
#include <QMediaPlayer>
#include <qmediaplayer.h>
#include "Card.h"
#include "IAudioPluginWrapper.h"
#include "Media.h"

namespace Ui {
class AudiosWidget;
}

class AudiosWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudiosWidget(std::unique_ptr<IAudioPluginWrapper> audioPlugin,
                        QWidget *parent = nullptr);
    ~AudiosWidget();

public slots:
    void addAudio(SourceWithAdditionalInfo audio, bool isLocal, bool isChosen = false);
    void load(QString word = "go", int batch_size = 5);

private:
    Ui::AudiosWidget *ui;
    QGridLayout *gridLayout;
    QMediaPlayer *mediaPlayer;
    std::unique_ptr<IAudioPluginWrapper> audioPlugin_;
};

#endif // AUDIOSWIDGET_HPP
