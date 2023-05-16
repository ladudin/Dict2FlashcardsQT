#ifndef EXAMPLESMODEL_H
#define EXAMPLESMODEL_H

#include <QAbstractListModel>
#include <string>
#include <vector>
#include <memory>

class ExamplesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ExamplesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setExamples(std::vector<std::string> new_examples);

private:
    std::vector<std::string> examples;
};

#endif // EXAMPLESMODEL_H
