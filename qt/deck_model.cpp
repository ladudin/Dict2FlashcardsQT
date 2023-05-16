#include "deck_model.h"
#include <QString>

DeckModel::DeckModel(std::shared_ptr<IDeck> deck, QObject *parent)
    : QAbstractListModel(parent)
    , deck(deck)
{
}

int DeckModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return deck->size();
}

QVariant DeckModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role)
    {
    case Qt::DisplayRole:
        return QString::fromStdString(deck->getWord(index.row()));
    case CardRole:
        return QVariant::fromValue(deck->getCard(index.row()));
    default:
        return QVariant();
    }
    return QVariant();
}

int DeckModel::indexOfWord(const QString &word)
{
    return deck->indexOfWord(word.toStdString());
}

QModelIndex DeckModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || row >= rowCount() || column != 0)
    {
        return QModelIndex();
    }
    return createIndex(row, 0);
}

void DeckModel::load(const QString &word)
{
    beginResetModel();
    deck->load(word.toStdString());
    endResetModel();
}

void DeckModel::next(const QModelIndex &index)
{
    deck->next(index.row());
}

void DeckModel::prev(const QModelIndex &index)
{
    deck->prev(index.row());
}
