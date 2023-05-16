#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "deck_model.h"
#include "examples_model.h"
#include "audio_model.h"
#include "images_model.h"
#include "card.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchReturned();
    void updateCardFields();
    void updateWord(Card*);
    void updateDefinition(Card*);
    void updateTags(Card*);
    void updateExamples(Card*);
    void updateAudio(Card*);
    void updateImages(Card*);
    void setCurrentIndex(QModelIndex);
    void onNextClicked();
    void onPrevClicked();

private:
    Ui::MainWindow *ui;
    DeckModel* deck_model;
    ExamplesModel* examples_model;
    AudioModel* audio_model;
    ImagesModel* images_model;
    QModelIndex current_index;
};
#endif // MAINWINDOW_H
