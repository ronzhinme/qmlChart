#ifndef POINTSLISTMODEL_H
#define POINTSLISTMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QPointF>

class FilterPointsProxyModel: public QSortFilterProxyModel
{
    // QSortFilterProxyModel interface
protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
};

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
    Q_INVOKABLE void setLeftTopViewPortPoint(qreal x, qreal y);
    Q_INVOKABLE void setRightBottomViewPortPoint(qreal x, qreal y);
    Q_INVOKABLE QPointF getLeftTopViewPortPoint() const;
    Q_INVOKABLE QPointF getRightBottomViewPortPoint() const;
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
private:
    QList<QPointF> points_;
    QPointF leftTopPoint_;
    QPointF rightBottomPoint_;
    QPointF leftTopViewPortPoint_;
    QPointF rightBottomViewPortPoint_;

    void updateLeftTopPoint_(const QPointF &point);
    void updateRightBottomPoint_(const QPointF &point);
};

#endif // POINTSLISTMODEL_H
