#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "deck_model.h"
#include "examples_model.h"
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
    void onWordCardsClicked(QModelIndex);
    void updateCardFields();
    void updateWord(Card*);
    void updateDefinition(Card*);
    void updateTags(Card*);
    void updateSentences(Card*);
    void setCurrentIndex(QModelIndex);
    void onNextClicked();
    void onPrevClicked();

signals:
    void cardChanged(Card*);

private:
    Ui::MainWindow *ui;
    DeckModel* deck_model;
    ExamplesModel* examples_model;
    // Card* current_card;
    QModelIndex current_index;
};
#endif // MAINWINDOW_H
