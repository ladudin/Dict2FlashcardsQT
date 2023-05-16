#ifndef IMAGESMODEL_H
#define IMAGESMODEL_H

#include <QAbstractListModel>
#include <string>
#include <vector>
#include <memory>

class ImagesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ImagesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setImages(std::vector<std::string> new_images_links);

private:
    std::vector<std::string> images_links;
};

#endif // IMAGESMODEL_H
