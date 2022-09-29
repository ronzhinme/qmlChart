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
    model_ = val;
    emit modelChanged();
    update();
}


void Graph::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    update();
    QQuickItem::geometryChange(newGeometry, oldGeometry);
}

QSGNode *Graph::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
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
        pointsModel->updateViewPort(width(), height(), 0, 0);

        QSGGeometry *geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
        geometry->setDrawingMode(QSGGeometry::DrawLines);
        //geometry->setLineWidth(2.5);

        auto pointIndex = 0;
        for(auto row = 0; row < pointsModel->getFilterModel()->rowCount(); ++row)
        {
            auto index = pointsModel->getFilterModel()->index(row,0);
            auto value = pointsModel->getFilterModel()->data(index);
            if(value.isValid())
            {
                auto point = value.toPointF();
                geometry->vertexDataAsPoint2D()[pointIndex++].set(point.x(),point.y());
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
