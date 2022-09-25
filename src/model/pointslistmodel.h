#ifndef POINTSLISTMODEL_H
#define POINTSLISTMODEL_H

#include <QAbstractListModel>
#include <QPointF>

class PointsListModel : public QAbstractListModel
{
    Q_OBJECT;
public:
    PointsListModel();
    ~PointsListModel() = default;

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

private:
    QList<QPointF> points_;
    QPointF leftTopPoint_;
    QPointF rightBottomPoint_;
};

#endif // POINTSLISTMODEL_H
