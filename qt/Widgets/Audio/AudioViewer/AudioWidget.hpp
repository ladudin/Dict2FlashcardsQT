#ifndef AUDIOWIDGET_HPP
#define AUDIOWIDGET_HPP

#include <QWidget>
#include <vector>
#include <string>
#include <QFormLayout>
#include <QPushButton>
#include "Media.h"
// #include "DefinitionsProviderWrapper.h"

namespace Ui {
class AudioWidget;
}

class AudioWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AudioWidget(QWidget *parent = nullptr);
    ~AudioWidget();

public slots:
    void set(Media audio);
    void next();
    void prev();
    Media extract();

private slots:
    void clear();
    void setButtonEnabled(QPushButton* button, bool enabled);
    void setButtonChosen(QPushButton* button);
    void updateChosen(size_t index, bool choice, QPushButton* button);

private:
    Ui::AudioWidget *ui;
    Media m_audio;
    std::vector<bool> chosen;
    QFormLayout* formLayout;
    const size_t audioInPage = 3;
    size_t pageNumber;
};

#endif // AUDIOWIDGET_HPP
