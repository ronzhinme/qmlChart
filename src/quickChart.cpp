#include "quickChart.h"

Graph::Graph()
    : model_(Q_NULLPTR)
{
    setFlag(ItemHasContents, true);
}

QAbstractListModel *Graph::getModel() const
{
    return model_;
}

void Graph::setModel(QAbstractListModel *val)
{
    model_ = val;
    emit modelChanged();
}


void Graph::geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry)
{
}

QSGNode *Graph::updatePaintNode(QSGNode *, UpdatePaintNodeData *)
{
    return nullptr;
}
