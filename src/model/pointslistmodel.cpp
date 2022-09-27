#include "pointslistmodel.h"

PointsListModel::PointsListModel()
    : filterModel_(new FilterPointsProxyModel())
{
    filterModel_->setSourceModel(this);
}

void PointsListModel::insertPoint(int index, const QPointF &point)
{
    if(index < 0 || index >= rowCount())
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());

        updateLeftTopPoint_(point);
        updateRightBottomPoint_(point);

        points_.append(point);
        endInsertRows();
        return;
    }

    beginInsertRows(QModelIndex(), index, index);
    points_.insert(index, point);
    endInsertRows();
}

void PointsListModel::deletePoint(int index)
{
    if(index < 0 || index >= rowCount())
    {
        return;
    }

    beginRemoveRows(QModelIndex(), index, index);
    points_.removeAt(index);
    endRemoveRows();
}

QVariant PointsListModel::getPoint(int index) const
{
    return data( this->index(index, 0), Qt::DisplayRole);
}

QPointF PointsListModel::getLeftTopPoint() const
{
    return leftTopPoint_;
}

QPointF PointsListModel::getRightBottomPoint() const
{
    return rightBottomPoint_;
}

void PointsListModel::setLeftTopViewPortPoint(qreal x, qreal y)
{
    leftTopViewPortPoint_.setX(x);
    leftTopViewPortPoint_.setY(y);
    filterModel_->setFilterFixedString("");
}

void PointsListModel::setRightBottomViewPortPoint(qreal x, qreal y)
{
    rightBottomViewPortPoint_.setX(x);
    rightBottomViewPortPoint_.setY(y);
    filterModel_->setFilterFixedString("");
}

QPointF PointsListModel::getLeftTopViewPortPoint() const
{
    return leftTopViewPortPoint_;
}

QPointF PointsListModel::getRightBottomViewPortPoint() const
{
    return rightBottomViewPortPoint_;
}

QSortFilterProxyModel *PointsListModel::getFilterModel() const
{
    return filterModel_.get();
}

int PointsListModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return points_.count();
}

QVariant PointsListModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()
            || index.row() < 0
            || index.row() >= points_.count()
            || role != Qt::ItemDataRole::DisplayRole)
    {
        return QVariant();
    }

    const auto point = points_.at(index.row());
    return QVariant::fromValue(point);
}

void PointsListModel::updateLeftTopPoint_(const QPointF &point)
{
    if(leftTopPoint_.x() > point.x())
    {
        leftTopPoint_.setX(point.x());
    }

    if(leftTopPoint_.y() > point.y())
    {
        leftTopPoint_.setY(point.y());
    }
}

void PointsListModel::updateRightBottomPoint_(const QPointF &point)
{
    if(rightBottomPoint_.x() < point.x())
    {
        rightBottomPoint_.setX(point.x());
    }

    if(rightBottomPoint_.y() < point.y())
    {
        rightBottomPoint_.setY(point.y());
    }
}


QVariant FilterPointsProxyModel::getPoint(int index) const
{
    const auto srcModel = static_cast<PointsListModel*>(sourceModel());
    if(!srcModel)
    {
        return QVariant();
    }

    return srcModel->getPoint(index);
}

bool FilterPointsProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent);

    const auto srcModel = static_cast<PointsListModel*>(sourceModel());
    if(!srcModel)
    {
        return false;
    }

    const auto srcObject = srcModel->getPoint(sourceRow);
    if(sourceRow > 0)
    {
        const auto srcPrevObject = srcModel->getPoint(sourceRow - 1);
        if(!srcObject.isValid() || !srcPrevObject.isValid())
        {
            return false;
        }

        if( lineVisibleInViewPort_(srcPrevObject.toPointF(), srcObject.toPointF()) )
        {
            return true;
        }
    }

    return false;
}

bool FilterPointsProxyModel::lineVisibleInViewPort_(const QPointF &lineBeginPoint, const QPointF &lineEndPoint) const
{
    const auto srcModel = static_cast<PointsListModel*>(sourceModel());
    if(!srcModel)
    {
        return false;
    }

    const auto ltPoint = srcModel->getLeftTopViewPortPoint();
    const auto rbPoint = srcModel->getRightBottomViewPortPoint();

    const auto isIntersectLeftBorder = isIntersect_(lineBeginPoint, lineEndPoint, ltPoint, QPointF(ltPoint.x(), rbPoint.y()));
    const auto isIntersectTopBorder = isIntersect_(lineBeginPoint, lineEndPoint, ltPoint, QPointF(rbPoint.x(), ltPoint.y()));
    const auto isIntersectRightBorder = isIntersect_(lineBeginPoint, lineEndPoint, QPointF(rbPoint.x(), ltPoint.y()), QPointF(rbPoint.x(), rbPoint.y()));
    const auto isIntersectBottomBorder = isIntersect_(lineBeginPoint, lineEndPoint, QPointF(ltPoint.x(), rbPoint.y()), QPointF(rbPoint.x(), rbPoint.y()));
    const auto isInsideViewPort = lineBeginPoint.x() >= ltPoint.x()
            && lineEndPoint.x() <= rbPoint.x()
            && lineBeginPoint.y() >= ltPoint.y()
            && lineEndPoint.y() <= rbPoint.y();

    return isIntersectLeftBorder
            || isIntersectTopBorder
            || isIntersectRightBorder
            || isIntersectBottomBorder
            || isInsideViewPort;
}

bool FilterPointsProxyModel::isIntersect_(const QPointF &a1, const QPointF &a2, const QPointF &b1, const QPointF &b2) const
{
    const auto v1 =(b2.x()-b1.x())*(a1.y()-b1.y())-(b2.y()-b1.y())*(a1.x()-b1.x());
    const auto v2 =(b2.x()-b1.x())*(a2.y()-b1.y())-(b2.y()-b1.y())*(a2.x()-b1.x());
    const auto v3 =(a2.x()-a1.x())*(b1.y()-a1.y())-(a2.y()-a1.y())*(b1.x()-a1.x());
    const auto v4 =(a2.x()-a1.x())*(b2.y()-a1.y())-(a2.y()-a1.y())*(b2.x()-a1.x());
    return (v1*v2<0) && (v3*v4<0);
}
