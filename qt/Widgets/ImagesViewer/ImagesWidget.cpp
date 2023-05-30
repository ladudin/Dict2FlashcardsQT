#include "ImagesWidget.hpp"
#include "ui_ImagesWidget.h"
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <algorithm>
// #include <qt6/QtCore/qsize.h>

IMagesWidget::IMagesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IMagesWidget),
    pageNumber(0)
{
    ui->setupUi(this);
    manager = new QNetworkAccessManager(this);
    gridLayout = new QGridLayout;
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            QPushButton* button = new QPushButton;
            button->setStyleSheet("background-color: white");
            connect(button, &QPushButton::clicked, [=](bool toggled) {
                    updateChosen(row * cols + col, toggled, button);
                });
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setCheckable(true);
            gridLayout->addWidget(button, row, col);
        }
    }
    ui->groupBox->setLayout(gridLayout);
}

IMagesWidget::~IMagesWidget()
{
    delete ui;
}

void IMagesWidget::setButtonEnabled(QPushButton* button, bool enabled) {
    if (enabled) {
        button->setEnabled(true);
        button->setChecked(false);
        button->setStyleSheet("background-color: white");
    }
    else {
        button->setStyleSheet("background-color: gray");
        button->setChecked(false);
        button->setEnabled(false);
    }
}
void IMagesWidget::setButtonChosen(QPushButton* button) {
    button->setStyleSheet("background-color: green");
}

void IMagesWidget::set(Media images)
{
    m_images = images;
    clear();
    chosen.resize(m_images.web.size());
    std::fill(chosen.begin(), chosen.end(), false);
    for (size_t i = 0; i < rows * cols; ++i) {
        if (i >= images.web.size()) {
            return;
        }
        else {
            QUrl imageUrl(QString::fromStdString(m_images.web.at(i).src));
            QNetworkReply *reply = manager->get(QNetworkRequest(imageUrl));
            QLayoutItem* item = gridLayout->itemAtPosition(i / cols, i % cols);
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            setButtonEnabled(button, true);
            connect(reply, &QNetworkReply::finished, [=]() {
                if (reply->error() == QNetworkReply::NoError) {
                    QImage image;
                    image.loadFromData(reply->readAll());
                    button->setIcon(QIcon(QPixmap::fromImage(image)));
                    button->setIconSize(QSize(150, 150));
                }
                reply->deleteLater();
            });
        }
    }
}

Media IMagesWidget::extract()
{
    Media media;
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (chosen[i]) {
            media.web.push_back(m_images.web.at(i));
        }
    }
    return media;
}

void IMagesWidget::updateChosen(size_t index, bool choice, QPushButton* button)
{
    if (chosen.size() <= index) {
        return;
    }
    chosen.at(index) = choice;
    if (choice) {
        button->setStyleSheet("background-color: green");
    }
    else {
        button->setStyleSheet("background-color: white");
    }
    qDebug() << extract().web.size();
}

void IMagesWidget::clear() {
    for (size_t row = 0; row < rows; ++row) {
        for (size_t col = 0; col < cols; ++col) {
            QLayoutItem* item = gridLayout->itemAtPosition(row, col);
            QPushButton* button = qobject_cast<QPushButton*>(item->widget());
            button->setIcon(QIcon());
            setButtonEnabled(button, false);
        }
    }
}