#include "examples_model.h"


ExamplesModel::ExamplesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ExamplesModel::rowCount(const QModelIndex &parent) const
{
    return examples->size();
}

QVariant ExamplesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return 0;
    switch (role) {
    case Qt::DisplayRole:
        return QString::fromStdString(examples->at(index.row()));
    default:
        return QVariant();
    }
    return QVariant();
}

void ExamplesModel::setExamples(Examples new_examples)
{
    examples = new_examples;
}
