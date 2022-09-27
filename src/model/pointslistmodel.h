#ifndef POINTSLISTMODEL_H
#define POINTSLISTMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QPointF>

class FilterPointsProxyModel: public QSortFilterProxyModel
{
public:
    Q_INVOKABLE QVariant getPoint(int index) const;

    // QSortFilterProxyModel interface
protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
    bool lineVisibleInViewPort_(const QPointF &lineBeginPoint, const QPointF &lineEndPoint) const;
    bool isIntersect_(const QPointF &a1, const QPointF &a2
                                    , const QPointF &b1, const QPointF &b2) const;
};

class PointsListModel : public QAbstractListModel
{
    Q_OBJECT;
    Q_PROPERTY(QSortFilterProxyModel* filterModel READ getFilterModel CONSTANT)
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

    QSortFilterProxyModel* getFilterModel() const;

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
    QScopedPointer<FilterPointsProxyModel> filterModel_;
    void updateLeftTopPoint_(const QPointF &point);
    void updateRightBottomPoint_(const QPointF &point);
};

#endif // POINTSLISTMODEL_H
