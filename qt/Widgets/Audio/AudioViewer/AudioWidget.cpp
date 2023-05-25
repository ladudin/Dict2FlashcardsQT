#include "AudioWidget.hpp"
#include "ui_AudioWidget.h"
#include <QCheckBox>
#include <QPushButton>
#include "AudioPlayer.hpp"

AudioWidget::AudioWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudioWidget),
    pageNumber(0)
{
    ui->setupUi(this);
    formLayout = new QFormLayout;
    for (size_t i = 0; i < audioInPage; ++i) {
        QPushButton* button = new QPushButton;
        button->setStyleSheet("background-color: white");
        button->setCheckable(true);
        button->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        connect(button, &QPushButton::clicked, [=](bool toggled) {
                updateChosen(i, toggled, button);
            });
        AudioPlayer* audioPlayer = new AudioPlayer;
        formLayout->addRow(button, audioPlayer);
    }
    ui->groupBox->setLayout(formLayout);
}

AudioWidget::~AudioWidget()
{
    delete ui;
}

void AudioWidget::setButtonEnabled(QPushButton* button, bool enabled) {
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
void AudioWidget::setButtonChosen(QPushButton* button) {
    button->setStyleSheet("background-color: green");
}

void AudioWidget::set(Media audio)
{
    m_audio = audio;
    clear();
    chosen.resize(m_audio.web.size());
    std::fill(chosen.begin(), chosen.end(), false);
    for (size_t i = 0; i < audioInPage; ++i) {
        QLayoutItem* button_item = formLayout->itemAt(i, QFormLayout::LabelRole);
        QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
        QLayoutItem* player_item = formLayout->itemAt(i, QFormLayout::FieldRole);
        AudioPlayer* player = qobject_cast<AudioPlayer*>(player_item->widget());
        if (i >= audio.web.size()) {
            return;
        }
        else {
            setButtonEnabled(button, true);
            player->set(audio.web.at(i), false);
        }
    }
}

void AudioWidget::next()
{

}

void AudioWidget::prev()
{

}

Media AudioWidget::extract()
{
    Media media;
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (chosen[i]) {
            media.web.push_back(m_audio.web.at(i));
        }
    }
    return media;
}

void AudioWidget::updateChosen(size_t index, bool choice, QPushButton *button)
{
    if (chosen.size() <= index) {
        return;
    }
    chosen.at(index) = choice;
    if (choice) {
        setButtonChosen(button);
    }
    else {
        setButtonEnabled(button, true);
    }
    qDebug() << extract().web.size();
}

void AudioWidget::clear() {
    for (size_t i = 0; i < audioInPage; ++i) {
        QLayoutItem* button_item = formLayout->itemAt(i, QFormLayout::LabelRole);
        QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
        setButtonEnabled(button, false);
        // QLayoutItem* player_item = formLayout->itemAt(i, QFormLayout::FieldRole);
        // AudioPlayer* player = qobject_cast<AudioPlayer*>(player_item->widget());  
    }
}