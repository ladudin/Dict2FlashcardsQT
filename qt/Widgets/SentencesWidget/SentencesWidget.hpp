#ifndef SENTENCESWIDGET_HPP
#define SENTENCESWIDGET_HPP

#include <QWidget>
#include <QGridLayout>
#include <memory>
#include "ISentencePluginWrapper.h"

namespace Ui {
class SentencesWidget;
}

class SentencesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SentencesWidget(std::unique_ptr<ISentencePluginWrapper> sentencePlugin,
                            QWidget *parent = nullptr);
    ~SentencesWidget();

public slots:
    void addSentence(QString sentence = QString(), bool is_chosen = false);
    void load(QString word, int batch_size = 5);
    void clear();

private:
    Ui::SentencesWidget *ui;
    QGridLayout *gridLayout;
    std::unique_ptr<ISentencePluginWrapper> sentencePlugin_;
};

#endif // SENTENCESWIDGET_HPP
