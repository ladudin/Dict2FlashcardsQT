#ifndef AUDIOMODEL_H
#define AUDIOMODEL_H

#include <QAbstractListModel>
#include <string>
#include <vector>
#include <memory>

class AudioModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AudioModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setAudio(std::vector<std::string> new_audio_links);

private:
    std::vector<std::string> audio_links;
};

#endif // AUDIOMODEL_H
