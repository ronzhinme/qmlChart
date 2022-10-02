#include "quickChart.h"

#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>

Graph::Graph(QQuickItem *parent)
    : QQuickItem(parent)
    , model_(Q_NULLPTR)
{
    setFlag(QQuickItem::ItemHasContents, true);
}

Graph::~Graph()
{
}

QAbstractListModel *Graph::getModel() const
{
    return model_;
}

void Graph::setModel(QAbstractListModel *val)
{
    if(model_)
    {
        const auto pointsModel = static_cast<PointsListModel*>(model_.get());
        if(pointsModel)
        {
            disconnect(pointsModel
                    , &PointsListModel::sigPositionChanged
                    , this
                    , &Graph::onPositionChanged_);
        }
    }

    model_ = val;
    emit modelChanged();
    update();

    if(model_)
    {
        const auto pointsModel = static_cast<PointsListModel*>(model_.get());
        if(pointsModel)
        {
            connect(pointsModel
                    , &PointsListModel::sigPositionChanged
                    , this
                    , &Graph::onPositionChanged_);
        }
    }
}


void Graph::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    update();
    QQuickItem::geometryChange(newGeometry, oldGeometry);
}

QSGNode *Graph::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    if(!model_)
    {
        return nullptr;
    }

    QSGGeometryNode *n = static_cast<QSGGeometryNode *>(node);
    const auto pointsModel = static_cast<PointsListModel*>(model_.get());

    auto material = new QSGFlatColorMaterial();
    material->setColor(QColor("orange"));

    if(n)
    {
        delete n;
        n = nullptr;
    }

    if (n == nullptr && pointsModel != nullptr)
    {
        const auto minX = pointsModel->getLeftTopPoint().x();
        const auto maxX = pointsModel->getRightBottomPoint().x();
        const auto minY = pointsModel->getLeftTopPoint().y();
        const auto maxY = pointsModel->getRightBottomPoint().y();
        const auto xPosition = pointsModel->getXPosition();
        const auto yPosition = pointsModel->getYPosition();
        pointsModel->updateViewPort(width(), height(), xPosition, yPosition);


        const auto pointsCount = pointsModel->getFilterModel()->rowCount();
        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), pointsCount * 2);
        geometry->setDrawingMode(QSGGeometry::DrawLines);
        //geometry->setLineWidth(2.5);

        auto pointIndex = 0;
        QPointF prevPoint;
        for(auto row = 0; row < pointsCount; ++row)
        {
            auto index = pointsModel->getFilterModel()->index(row,0);
            if(!index.isValid())
            {
                continue;
            }

            auto value = pointsModel->getFilterModel()->data(index);
            if(value.isValid())
            {
                const auto point = value.toPointF();
                const auto x = point.x() - (minX < 0 ? (((2 * maxX * xPosition) - maxX) - (width()/2))
                                                  : maxX * xPosition);
                const auto y = point.y() - (minY < 0 ? (((2 * maxY * yPosition) - maxY) - (height()/2))
                                                   : maxY * yPosition);

                if(pointIndex >0 && pointIndex % 2 == 0)
                {
                    geometry->vertexDataAsPoint2D()[pointIndex++].set(prevPoint.x(),prevPoint.y());
                }

                geometry->vertexDataAsPoint2D()[pointIndex++].set(x,y);
                prevPoint = QPointF(x,y);
            }
        }

        n = new QSGGeometryNode();
        n->setGeometry(geometry);
        n->setFlag(QSGNode::OwnsGeometry);
        n->setMaterial(material);
        n->setFlag(QSGNode::OwnsMaterial);
    }

    return n;
}

void Graph::onPositionChanged_()
{
    update();
}
