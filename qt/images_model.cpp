#include "images_model.h"

ImagesModel::ImagesModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ImagesModel::rowCount(const QModelIndex &parent) const
{
    return images_links.size();
}

QVariant ImagesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return 0;
    switch (role) {
    case Qt::DisplayRole:
        return QString::fromStdString(images_links.at(index.row()));
    default:
        return QVariant();
    }
    return QVariant();
}

void ImagesModel::setImages(std::vector<std::string> new_images_links)
{
    beginResetModel();
    images_links = new_images_links;
    endResetModel();
}

