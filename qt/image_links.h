#ifndef IMAGELINKS_H
#define IMAGELINKS_H

#include <QAbstractListModel>
#include <vector>
#include <string>

class ImageLinks : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ImageLinks(std::vector<std::string> image_links, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    std::vector<std::string> image_links;
};

#endif // IMAGELINKS_H
