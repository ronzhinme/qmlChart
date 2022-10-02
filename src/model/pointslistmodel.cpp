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

QList<QPointF> PointsListModel::getPoints() const
{
    return points_;
}

void PointsListModel::updateViewPort(float width, float height, float xPosition, float yPosition)
{
    const auto minX = getLeftTopPoint().x();
    const auto maxX = getRightBottomPoint().x();
    const auto minY = getLeftTopPoint().y();
    const auto maxY = getRightBottomPoint().y();

    const auto x = minX < 0 ? (2 * maxX * xPosition - maxX)
                            : maxX * xPosition;
    const auto y = minY < 0 ? (2 * maxY * yPosition - maxY)
                            : maxY * yPosition;

    const auto x1 = x + width;
    const auto y1 = y + height;

    setLeftTopViewPortPoint(x, y);
    setRightBottomViewPortPoint(x1, y1);
    setXPosition(xPosition);
    setYPosition(yPosition);
}

qreal PointsListModel::getXPosition() const
{
    return xyPosition_.x();
}

qreal PointsListModel::getYPosition() const
{
    return xyPosition_.y();
}

void PointsListModel::setYPosition(qreal val)
{
    xyPosition_.setY(val);
    emit sigPositionChanged(xyPosition_.x(), xyPosition_.y());
}

void PointsListModel::setXPosition(qreal val)
{
    xyPosition_.setX(val);
    emit sigPositionChanged(xyPosition_.x(), xyPosition_.y());
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
    if(!srcObject.isValid())
    {
        return false;
    }

    if(sourceRow > 0)
    {
        const auto srcPrevObject = srcModel->getPoint(sourceRow - 1);
        if(!srcPrevObject.isValid())
        {
            return false;
        }

        if( lineVisibleInViewPort_(srcPrevObject.toPointF(), srcObject.toPointF()) )
        {
            return true;
        }
    }
    else
    {
        return isInViewPort_(srcObject.toPointF());
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
    const auto rtPoint = QPointF(rbPoint.x(), ltPoint.y());
    const auto lbPoint = QPointF(ltPoint.x(), rbPoint.y());

    const auto isIntersectLeftBorder = isIntersect_(lineBeginPoint, lineEndPoint, ltPoint, lbPoint);
    const auto isIntersectTopBorder = isIntersect_(lineBeginPoint, lineEndPoint, ltPoint, rtPoint);
    const auto isIntersectRightBorder = isIntersect_(lineBeginPoint, lineEndPoint, rtPoint, rbPoint);
    const auto isIntersectBottomBorder = isIntersect_(lineBeginPoint, lineEndPoint, lbPoint, rbPoint);

    const auto isInsideViewPort = isInViewPort_(lineBeginPoint)
            || isInViewPort_(lineEndPoint);

//    qDebug() << __FUNCTION__ << isInsideViewPort << lineBeginPoint.x() << lineBeginPoint.y();

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

bool FilterPointsProxyModel::isInViewPort_(const QPointF &point) const
{
    const auto srcModel = static_cast<PointsListModel*>(sourceModel());
    if(!srcModel)
    {
        return false;
    }

    const auto ltPoint = srcModel->getLeftTopViewPortPoint();
    const auto rbPoint = srcModel->getRightBottomViewPortPoint();

    return (point.x() >= ltPoint.x() && point.x() <= rbPoint.x())
            || (point.x() >= ltPoint.x() && point.x() <= rbPoint.x());
}
