#ifndef AUDIOLINKS_H
#define AUDIOLINKS_H

#include <QAbstractListModel>
#include <vector>
#include <string>

class AudioLinks : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit AudioLinks(std::vector<std::string> audio_links, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<std::string> audio_links;
};

#endif // AUDIOLINKS_H
