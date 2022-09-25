#ifndef POINTSLISTMODEL_H
#define POINTSLISTMODEL_H

#include <QAbstractListModel>

class PointsListModel : public QAbstractListModel
{
    Q_OBJECT;
public:
    PointsListModel();
    ~PointsListModel() = default;
};

#endif // POINTSLISTMODEL_H
