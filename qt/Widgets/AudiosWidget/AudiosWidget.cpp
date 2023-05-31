#include "AudiosWidget.hpp"
#include "ui_AudiosWidget.h"

AudiosWidget::AudiosWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AudiosWidget)
{
    ui->setupUi(this);
}

AudiosWidget::~AudiosWidget()
{
    delete ui;
}
