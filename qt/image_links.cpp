#include "image_links.h"

ImageLinks::ImageLinks(std::vector<std::string> image_links, QObject *parent)
    : QAbstractListModel(parent)
    , image_links(image_links)
{
}

int ImageLinks::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return image_links.size();
}

QVariant ImageLinks::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return QString::fromStdString(image_links.at(index.row()));
    default:
        return QVariant();
    }
    return QVariant();
}
