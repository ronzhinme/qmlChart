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

    void insertPoint(int index, const QPointF &point);
    void deletePoint(int index);
    Q_INVOKABLE QVariant getPoint(int index) const;
    Q_INVOKABLE QPointF getLeftTopPoint() const;
    Q_INVOKABLE QPointF getRightBottomPoint() const;
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
private:
    QList<QPointF> points_;
    QPointF leftTopPoint_;
    QPointF rightBottomPoint_;

    void updateLeftTopPoint_(const QPointF &point);
    void updateRightBottomPoint_(const QPointF &point);
};

#endif // POINTSLISTMODEL_H
