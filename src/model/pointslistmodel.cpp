#include "pointslistmodel.h"

PointsListModel::PointsListModel()
{
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
}

void PointsListModel::setRightBottomViewPortPoint(qreal x, qreal y)
{
    rightBottomPoint_.setX(x);
    rightBottomPoint_.setY(y);
}

QPointF PointsListModel::getLeftTopViewPortPoint() const
{
    return leftTopViewPortPoint_;
}

QPointF PointsListModel::getRightBottomViewPortPoint() const
{
    return rightBottomViewPortPoint_;
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


bool FilterPointsProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    Q_UNUSED(sourceParent);

    const auto srcModel = static_cast<PointsListModel*>(sourceModel());
    const auto srcObject = srcModel->getPoint(sourceRow);
    if(srcObject.isValid())
    {
        const auto srcPoint = srcObject.toPointF();
        return srcPoint.x() >= srcModel->getLeftTopViewPortPoint().x()
                && srcPoint.x() <= srcModel->getRightBottomViewPortPoint().x()
                && srcPoint.y() >= srcModel->getLeftTopViewPortPoint().y()
                && srcPoint.y() <= srcModel->getRightBottomViewPortPoint().y();
    }

    return false;
}
