#include "audiolinks.h"

AudioLinks::AudioLinks(std::vector<std::string> audio_links, QObject *parent)
    : QAbstractListModel(parent)
    , audio_links(audio_links)
{
}

int AudioLinks::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return audio_links.size();
}

QVariant AudioLinks::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return QString::fromStdString(audio_links.at(index.row()));
    default:
        return QVariant();
    }
    return QVariant();
}
