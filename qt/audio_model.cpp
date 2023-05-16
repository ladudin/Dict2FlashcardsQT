#include "audio_model.h"

AudioModel::AudioModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int AudioModel::rowCount(const QModelIndex &parent) const
{
    return audio_links.size();
}

QVariant AudioModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return 0;
    switch (role) {
    case Qt::DisplayRole:
        return QString::fromStdString(audio_links.at(index.row()));
    default:
        return QVariant();
    }
    return QVariant();
}

void AudioModel::setAudio(std::vector<std::string> new_audio_links)
{
    beginResetModel();
    audio_links = new_audio_links;
    endResetModel();
}

