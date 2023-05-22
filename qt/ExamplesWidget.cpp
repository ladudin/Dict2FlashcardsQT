#include "ExamplesWidget.hpp"
#include "ui_ExamplesWidget.h"
#include <QFormLayout>
#include <QTextEdit>
#include <QPushButton>
#include <algorithm>
#include <iostream>
#include <qpushbutton.h>
#include <qsizepolicy.h>

ExamplesWidget::ExamplesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExamplesWidget),
    examples(nullptr),
    page_number(0)
{
    ui->setupUi(this);
    form_layout = new QFormLayout;
    for (size_t i = 0; i < edits_in_page; ++i) {
        QTextEdit* edit = new QTextEdit;
        edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        QPushButton* button = new QPushButton;
        button->setStyleSheet("background-color: white");
        button->setCheckable(true);
        button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        connect(button, &QPushButton::toggled, [=](bool toggled) {
                updateChosen(i, toggled, button);
            });
        form_layout->addRow(edit, button);
    }
    ui->groupBox->setLayout(form_layout);
}

ExamplesWidget::~ExamplesWidget()
{
    delete ui;
}

void ExamplesWidget::setButtonEnabled(QPushButton* button, bool enabled) {
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

void ExamplesWidget::setButtonChosen(QPushButton* button) {
    button->setStyleSheet("background-color: green");
}

void ExamplesWidget::set(const std::vector<std::string> *new_examples)
{
    examples = new_examples;
    if (!examples) {
        return;
    }
    clear();
    chosen.resize(examples->size());
    for (size_t i = 0; i < edits_in_page; ++i) {
        QLayoutItem* edit_item = form_layout->itemAt(i, QFormLayout::LabelRole);
        QTextEdit* edit = qobject_cast<QTextEdit*>(edit_item->widget());
        QLayoutItem* button_item = form_layout->itemAt(i, QFormLayout::FieldRole);
        QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
        if (i < examples->size()) {
            edit->setText(QString::fromStdString(examples->at(i)));
            edit->setEnabled(true);
            setButtonEnabled(button, true);
        }
        else {
        }
    }
}

void ExamplesWidget::next()
{
    size_t start_index = (page_number + 1) * edits_in_page;
    if (start_index >= examples->size()) {
        return;
    }
    clear();
    for (size_t i = 0; i < edits_in_page; ++i) {
        QLayoutItem* edit_item = form_layout->itemAt(i, QFormLayout::LabelRole);
        QTextEdit* edit = qobject_cast<QTextEdit*>(edit_item->widget());
        QLayoutItem* button_item = form_layout->itemAt(i, QFormLayout::FieldRole);
        QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
        if (start_index + i < examples->size()) {
            edit->setText(QString::fromStdString(examples->at(start_index + i)));
            edit->setEnabled(true);
            setButtonEnabled(button, true);
        }
        else {
        }
    }
    ++page_number;
}

void ExamplesWidget::prev()
{
    if (page_number == 0) {
        return;
    }
    clear();
    if (page_number == 1) {
        set(examples);
        --page_number;
        return;
    }
    page_number -= 2;
    next();
}

std::vector<std::string> ExamplesWidget::extract()
{
    std::vector<std::string> extracted;
    if (!examples) {
        return extracted;
    }
    for (size_t i = 0; i < chosen.size(); ++i) {
        if (chosen[i]) {
            extracted.push_back(examples->at(i));
        }
    }
    return extracted;
}

void ExamplesWidget::clear()
{
    for (size_t i = 0; i < edits_in_page; ++i) {
        QLayoutItem* item = form_layout->itemAt(i, QFormLayout::LabelRole);
        if (QTextEdit* edit = qobject_cast<QTextEdit*>(item->widget())) {
            edit->clear();
        }
        QLayoutItem* button_item = form_layout->itemAt(i, QFormLayout::FieldRole);
        QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
        setButtonEnabled(button, false);
    }
}

void ExamplesWidget::updateChosen(size_t index, bool choice, QPushButton *button)
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
}

