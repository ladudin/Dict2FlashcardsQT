#ifndef IMAGESWIDGET_H
#define IMAGESWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QNetworkAccessManager>
#include "Media.hpp"

namespace Ui {
class IMagesWidget;
}

class IMagesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit IMagesWidget(QWidget *parent = nullptr);
    ~IMagesWidget();

public slots:
    void set(Media images);
    Media extract();

private slots:
    void clear();
    void setButtonEnabled(QPushButton* button, bool enabled);
    void setButtonChosen(QPushButton* button);
    void updateChosen(size_t index, bool choice, QPushButton* button);

private:
    Ui::IMagesWidget *ui;
    Media m_images;
    std::vector<bool> chosen;
    size_t rows = 2;
    size_t cols = 3;
    size_t pageNumber;
    QGridLayout* gridLayout;
    QNetworkAccessManager* manager;
};

#endif // IMAGESWIDGET_H
