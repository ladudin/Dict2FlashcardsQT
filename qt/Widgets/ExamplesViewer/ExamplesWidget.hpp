#ifndef EXAMPLESWIDGET_H
#define EXAMPLESWIDGET_H

#include <QWidget>
#include <vector>
#include <string>
#include <QFormLayout>
#include <QPushButton>

namespace Ui {
class ExamplesWidget;
}

class ExamplesWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExamplesWidget(QWidget *parent = nullptr);
    ~ExamplesWidget();
public slots:
    void set(const std::vector<std::string>* new_examples, std::vector<bool> chosen=std::vector<bool>());
    void next();
    void prev();
    void setItemEnabled(size_t index, bool enabled);
    void setItemChosen(size_t index);
    std::vector<std::string> extract();

private slots:
    void clear();
    void updateChosen(size_t index, bool choice, QPushButton* button);

private:
    Ui::ExamplesWidget *ui;
    const std::vector<std::string>* examples;
    std::vector<bool> chosen_;
    QFormLayout* form_layout;
    const size_t edits_in_page = 3;
    size_t page_number;
};

#endif // EXAMPLESWIDGET_H
