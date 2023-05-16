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
    typedef std::vector<std::string>* Examples;
    explicit ExamplesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setExamples(Examples new_examples);

private:
    Examples examples;
};

#endif // EXAMPLESMODEL_H
