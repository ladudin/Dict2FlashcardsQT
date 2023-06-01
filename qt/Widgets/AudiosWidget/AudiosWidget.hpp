#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QWidget>
#include <QGridLayout>
#include <qgridlayout.h>
#include "Card.h"
#include "Media.h"

namespace Ui {
class AudiosWidget;
}

class AudiosWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudiosWidget(QWidget *parent = nullptr);
    ~AudiosWidget();

public slots:
    void addAudio(SourceWithAdditionalInfo audio, bool isLocal, bool isChosen);

private:
    Ui::AudiosWidget *ui;
    QGridLayout *gridLayout;
};

#endif // AUDIOSWIDGET_HPP
