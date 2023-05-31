#ifndef AUDIOSWIDGET_HPP
#define AUDIOSWIDGET_HPP

#include <QWidget>

namespace Ui {
class AudiosWidget;
}

class AudiosWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudiosWidget(QWidget *parent = nullptr);
    ~AudiosWidget();

private:
    Ui::AudiosWidget *ui;
};

#endif // AUDIOSWIDGET_HPP
