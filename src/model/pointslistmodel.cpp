#include "pointslistmodel.h"

PointsListModel::PointsListModel()
{
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

    return QVariant::fromValue(points_.at(index.row()));
}
