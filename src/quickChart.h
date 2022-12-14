#ifndef QUICKCHART_H
#define QUICKCHART_H

#include <QQuickItem>
#include "model/pointslistmodel.h"

class Graph : public QQuickItem
{
    Q_OBJECT;
    Q_PROPERTY(QAbstractListModel* model READ getModel WRITE setModel NOTIFY modelChanged);
    QML_NAMED_ELEMENT(QuickChart);
public:
    Graph(QQuickItem *parent = nullptr);
    ~Graph();

    QAbstractListModel* getModel() const;
    void setModel(QAbstractListModel* val);
signals:
    void modelChanged();

    // QQuickItem interface
protected:
    virtual void geometryChange(const QRectF &newGeometry, const QRectF &oldGeometry) override;
    virtual QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
private:
    QPointer<QAbstractListModel> model_;
private slots:
    void onPositionChanged_();
};

#endif // QUICKCHART_H
