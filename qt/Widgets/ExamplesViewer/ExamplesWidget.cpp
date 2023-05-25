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

void ExamplesWidget::setItemEnabled(size_t index, bool enabled) {
    QLayoutItem* edit_item = form_layout->itemAt(index, QFormLayout::LabelRole);
    QTextEdit* edit = qobject_cast<QTextEdit*>(edit_item->widget());
    QLayoutItem* button_item = form_layout->itemAt(index, QFormLayout::FieldRole);
    QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
    if (enabled) {
        edit->setEnabled(true);
        edit->setText(QString::fromStdString(examples->at(page_number * edits_in_page + index)));
        button->setEnabled(true);
        button->setChecked(false);
        button->setStyleSheet("background-color: white");
    }
    else {
        edit->setEnabled(true);
        edit->clear();
        edit->setEnabled(false);
        button->setEnabled(true);
        button->setChecked(false);
        button->setStyleSheet("background-color: gray");
        button->setEnabled(false);
    }
}

void ExamplesWidget::setItemChosen(size_t index) {
    QLayoutItem* button_item = form_layout->itemAt(index, QFormLayout::FieldRole);
    QPushButton* button = qobject_cast<QPushButton*>(button_item->widget());
    button->setEnabled(true);
    button->setChecked(true);
    button->setStyleSheet("background-color: green");
}

void ExamplesWidget::set(const std::vector<std::string> *new_examples, std::vector<bool> chosen)
{
    std::cout << "set при page_number " << page_number << std::endl;
    examples = new_examples;
    if (!examples) {
        return;
    }
    std::cout << "examples не пустой " << page_number << std::endl;
    clear();
    if (!chosen.empty()) {
        chosen_ = chosen;
    } 
    for (size_t i = chosen_.size(); i < examples->size(); ++i) {
        chosen_.push_back(false);
    }
    size_t examples_index = page_number * edits_in_page;
    for (size_t i = 0; i < edits_in_page; ++i) {
        if (examples_index + i < examples->size()) {
            setItemEnabled(i, true);
            if (chosen_.at(examples_index + i)) {
                setItemChosen(i);
            }
        }
    }
}

void ExamplesWidget::next()
{
    if (!examples) {
        return;
    }
    if (page_number * edits_in_page >= examples->size()) {
        return;
    }
    ++page_number;
    std::cout << "Увеличили page_number до " << page_number << std::endl;
    set(examples);
}

void ExamplesWidget::prev()
{
    if (!examples) {
        return;
    }
    if (page_number == 0) {
        return;
    }
    --page_number;
    std::cout << "Уменьшили page_number до " << page_number << std::endl;
    set(examples);
}

std::vector<std::string> ExamplesWidget::extract()
{
    std::vector<std::string> extracted;
    if (!examples) {
        return extracted;
    }
    for (size_t i = 0; i < chosen_.size(); ++i) {
        if (chosen_[i]) {
            extracted.push_back(examples->at(i));
        }
    }
    return extracted;
}

void ExamplesWidget::clear()
{
    for (size_t i = 0; i < edits_in_page; ++i) {
        setItemEnabled(i, false);
    }
}

void ExamplesWidget::updateChosen(size_t index, bool choice, QPushButton *button)
{
    if (chosen_.size() <= page_number * edits_in_page + index) {
        return;
    }
    chosen_.at(page_number * edits_in_page + index) = choice;
    if (choice) {
        setItemChosen(index);
    }
    else {
        setItemEnabled(index, true);
    }
}

