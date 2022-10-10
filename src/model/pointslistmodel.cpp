#include "pointslistmodel.h"

PointsListModel::PointsListModel()
    : filterModel_(new FilterPointsProxyModel())
    , autoScroll_(false, false)
    , scale_(1.0,1.0)
    , axisLimitEnabled_(false, false)
    , axisXLimit_(0, 0)
    , axisYLimit_(0, 0)
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
        onPointsChanged_();
        emit dataChanged(this->index(index), this->index(rowCount()-1));
    }
    else
    {
        beginInsertRows(QModelIndex(), index, index);
        points_.insert(index, point);
        endInsertRows();
        onPointsChanged_();
        emit dataChanged(this->index(index), this->index(index));
    }
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
    onPointsChanged_();
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

    const auto x = minX >= 0 ? maxX * xPosition
                             : (2 * maxX * xPosition - maxX);
    const auto y = minY >= 0 ? maxY * yPosition
                             : (2 * maxY * yPosition - maxY);

    const auto x1 = x + width;
    const auto y1 = y + height;

    setLeftTopViewPortPoint(x * (1 / scale_.x()), y * (1 / scale_.y()));
    setRightBottomViewPortPoint(x1 * (1 / scale_.x()), y1 * (1 / scale_.y()));
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

bool PointsListModel::getAutoScrollX() const
{
    return autoScroll_.first;
}

bool PointsListModel::getAutoScrollY() const
{
    return autoScroll_.first;
}

qreal PointsListModel::getScaleRatioX() const
{
    return scale_.x();
}

qreal PointsListModel::getScaleRatioY() const
{
    return scale_.y();
}

bool PointsListModel::getAxisXLimitEnabled() const
{
    return axisLimitEnabled_.first;
}

bool PointsListModel::getAxisYLimitEnabled() const
{
    return axisLimitEnabled_.second;
}

qreal PointsListModel::getAxisXLimitMin() const
{
    return axisXLimit_.first;
}

qreal PointsListModel::getAxisXLimitMax() const
{
    return axisXLimit_.second;
}

qreal PointsListModel::getAxisYLimitMin() const
{
    return axisYLimit_.first;
}

qreal PointsListModel::getAxisYLimitMax() const
{
    return axisYLimit_.second;
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

void PointsListModel::setAutoScrollX(bool val)
{
    autoScroll_.first = val;
    emit sigAutoScrollChanged(autoScroll_.first, autoScroll_.second);
}

void PointsListModel::setAutoScrollY(bool val)
{
    autoScroll_.second = val;
    emit sigAutoScrollChanged(autoScroll_.first, autoScroll_.second);
}

void PointsListModel::setScaleRatioX(qreal val)
{
    scale_.setX(val);
    emit sigScaleRatioChanged(scale_.x(), scale_.y());
}

void PointsListModel::setScaleRatioY(qreal val)
{
    scale_.setY(val);
    emit sigScaleRatioChanged(scale_.x(), scale_.y());
}

void PointsListModel::setAxisXLimitEnabled(bool val)
{
    axisLimitEnabled_.first = val;
    emit sigAxisLimitEnabledChanged(axisLimitEnabled_.first, axisLimitEnabled_.second);
}

void PointsListModel::setAxisYLimitEnabled(bool val)
{
    axisLimitEnabled_.second = val;
    emit sigAxisLimitEnabledChanged(axisLimitEnabled_.first, axisLimitEnabled_.second);
}

void PointsListModel::setAxisXLimitMin(qreal val)
{
    axisXLimit_.first = val;
    emit sigAxisXLimitChanged(axisXLimit_.first, axisXLimit_.second);
}

void PointsListModel::setAxisXLimitMax(qreal val)
{
    axisXLimit_.second = val;
    emit sigAxisXLimitChanged(axisXLimit_.first, axisXLimit_.second);
}

void PointsListModel::setAxisYLimitMin(qreal val)
{
    axisYLimit_.first = val;
    emit sigAxisYLimitChanged(axisYLimit_.first, axisYLimit_.second);
}

void PointsListModel::setAxisYLimitMax(qreal val)
{
    axisYLimit_.second = val;
    emit sigAxisYLimitChanged(axisYLimit_.first, axisYLimit_.second);
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

void PointsListModel::onPointsChanged_()
{
    if(autoScroll_.first
            || autoScroll_.second)
    {
        const auto lastPointVar = getPoint(rowCount() - 1);
        if(!lastPointVar.isValid())
        {
            return;
        }

        const auto lastPoint = lastPointVar.toPointF();
        const auto minViewPoint = getLeftTopViewPortPoint();
        const auto maxViewPoint = getRightBottomViewPortPoint();
        const auto width = maxViewPoint.x() - minViewPoint.x();
        const auto height = maxViewPoint.y() - minViewPoint.y();
        const auto minValPoint = getLeftTopPoint();
        const auto maxValPoint = getRightBottomPoint();

        auto xPos = getXPosition();
        auto yPos = getYPosition();

        if(autoScroll_.first)
        {
            xPos = minValPoint.x() >= 0 ? 0.0 : 0.5;
            xPos = lastPoint.x() >= width && lastPoint.x() >= maxValPoint.x()
                    ? 1 - (width / (maxValPoint.x() * (minValPoint.x() >= 0 ? 1 : 2)))
                    : xPos;
            xPos = lastPoint.x() <= minValPoint.x() ? 0.0 : xPos;
        }

        if(autoScroll_.second)
        {
            yPos = minValPoint.y() >= 0 ? 0.0 : 0.5;
            yPos = lastPoint.y() >= height && lastPoint.y() >= maxValPoint.y()
                    ? 1 - (height / (maxValPoint.y() * (minValPoint.y() >= 0 ? 1 : 2)))
                    : yPos;
            yPos = lastPoint.y() <= minValPoint.y() ? 0.0 : yPos;
        }

        updateViewPort(width, height, xPos, yPos);
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
