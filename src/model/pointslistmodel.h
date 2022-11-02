#ifndef POINTSLISTMODEL_H
#define POINTSLISTMODEL_H

#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QPointF>

class FilterPointsProxyModel: public QSortFilterProxyModel
{
public:
    Q_INVOKABLE QVariant getPoint(int index) const;

    // QSortFilterProxyModel interface
protected:
    virtual bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
    bool lineVisibleInViewPort_(const QPointF &lineBeginPoint, const QPointF &lineEndPoint) const;
    bool isIntersect_(const QPointF &a1, const QPointF &a2
                                    , const QPointF &b1, const QPointF &b2) const;
    bool isInViewPort_(const QPointF &point) const;
};

class PointsListModel : public QAbstractListModel
{
    Q_OBJECT;
    Q_PROPERTY(QSortFilterProxyModel* filterModel READ getFilterModel CONSTANT);
    Q_PROPERTY(qreal xPosition READ getXPosition WRITE setXPosition NOTIFY sigPositionChanged);
    Q_PROPERTY(qreal yPosition READ getYPosition WRITE setYPosition NOTIFY sigPositionChanged);
    Q_PROPERTY(bool autoScrollX READ getAutoScrollX WRITE setAutoScrollX NOTIFY sigAutoScrollChanged);
    Q_PROPERTY(bool autoScrollY READ getAutoScrollY WRITE setAutoScrollY NOTIFY sigAutoScrollChanged);
    Q_PROPERTY(qreal scaleRatioX READ getScaleRatioX WRITE setScaleRatioX NOTIFY sigScaleRatioChanged);
    Q_PROPERTY(qreal scaleRatioY READ getScaleRatioY WRITE setScaleRatioY NOTIFY sigScaleRatioChanged);
    Q_PROPERTY(bool axisXLimitEnabled READ getAxisXLimitEnabled WRITE setAxisXLimitEnabled NOTIFY sigAxisLimitEnabledChanged);
    Q_PROPERTY(bool axisYLimitEnabled READ getAxisYLimitEnabled WRITE setAxisYLimitEnabled NOTIFY sigAxisLimitEnabledChanged);
    Q_PROPERTY(qreal axisXLimitMin READ getAxisXLimitMin WRITE setAxisXLimitMin NOTIFY sigAxisXLimitChanged);
    Q_PROPERTY(qreal axisXLimitMax READ getAxisXLimitMax WRITE setAxisXLimitMax NOTIFY sigAxisXLimitChanged);
    Q_PROPERTY(qreal axisYLimitMin READ getAxisYLimitMin WRITE setAxisYLimitMin NOTIFY sigAxisYLimitChanged);
    Q_PROPERTY(qreal axisYLimitMax READ getAxisYLimitMax WRITE setAxisYLimitMax NOTIFY sigAxisYLimitChanged);
    Q_PROPERTY(bool autoFitX READ getAutoFitX WRITE setAutoFitX NOTIFY sigAutoFitChanged);
    Q_PROPERTY(bool autoFitY READ getAutoFitY WRITE setAutoFitY NOTIFY sigAutoFitChanged);
    Q_PROPERTY(bool invertX READ getInvertX WRITE setInvertX NOTIFY sigInvertChanged);
    Q_PROPERTY(bool invertY READ getInvertY WRITE setInvertY NOTIFY sigInvertChanged);
public:
    PointsListModel();
    ~PointsListModel() = default;

    void insertPoint(int index, const QPointF &point);
    void deletePoint(int index);
    Q_INVOKABLE QVariant getPoint(int index) const;
    Q_INVOKABLE QPointF getLeftTopPoint() const;
    Q_INVOKABLE QPointF getRightBottomPoint() const;
    Q_INVOKABLE void setLeftTopViewPortPoint(qreal x, qreal y);
    Q_INVOKABLE void setRightBottomViewPortPoint(qreal x, qreal y);
    Q_INVOKABLE QPointF getLeftTopViewPortPoint() const;
    Q_INVOKABLE QPointF getRightBottomViewPortPoint() const;

    QSortFilterProxyModel* getFilterModel() const;
    QList<QPointF> getPoints() const;
    Q_INVOKABLE void updateViewPort(float width, float height, float xPosition, float yPosition);

    qreal getXPosition() const;
    qreal getYPosition() const;
    bool getAutoScrollX() const;
    bool getAutoScrollY() const;
    qreal getScaleRatioX() const;
    qreal getScaleRatioY() const;
    bool getAxisXLimitEnabled() const;
    bool getAxisYLimitEnabled() const;
    qreal getAxisXLimitMin() const;
    qreal getAxisXLimitMax() const;
    qreal getAxisYLimitMin() const;
    qreal getAxisYLimitMax() const;
    bool getAutoFitX() const;
    bool getAutoFitY() const;
    bool getInvertX() const;
    bool getInvertY() const;

    void setYPosition(qreal val);
    void setXPosition(qreal val);
    void setAutoScrollX(bool val);
    void setAutoScrollY(bool val);
    void setScaleRatioX(qreal val);
    void setScaleRatioY(qreal val);
    void setAxisXLimitEnabled(bool val);
    void setAxisYLimitEnabled(bool val);
    void setAxisXLimitMin(qreal val);
    void setAxisXLimitMax(qreal val);
    void setAxisYLimitMin(qreal val);
    void setAxisYLimitMax(qreal val);
    void setAutoFitX(bool val);
    void setAutoFitY(bool val);
    void setInvertX(bool val);
    void setInvertY(bool val);
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
private:
    QList<QPointF> points_;
    QPointF leftTopPoint_;
    QPointF rightBottomPoint_;
    QPointF leftTopViewPortPoint_;
    QPointF rightBottomViewPortPoint_;
    QScopedPointer<FilterPointsProxyModel> filterModel_;
    void updateLeftTopPoint_(const QPointF &point);
    void updateRightBottomPoint_(const QPointF &point);
    QPointF xyPosition_;
    QPair<bool, bool> autoScroll_;
    QPointF scale_;
    QPair<bool, bool> axisLimitEnabled_;
    QPair<qreal, qreal> axisXLimit_;
    QPair<qreal, qreal> axisYLimit_;
    QPair<bool, bool> autofitAxis_;
    QPair<bool, bool> invertAxis_;
signals:
    void sigPositionChanged(qreal x, qreal y);
    void sigAutoScrollChanged(bool x, bool y);
    void sigScaleRatioChanged(qreal ratioX, qreal ratioY);
    void sigAxisLimitEnabledChanged(bool axisX, bool axisY);
    void sigAxisXLimitChanged(qreal min, qreal max);
    void sigAxisYLimitChanged(qreal min, qreal max);
    void sigAutoFitChanged(bool autoFitX, bool autoFitY);
    void sigInvertChanged(bool invertX, bool invertY);
private slots:
    void onPointsChanged_();
};

#endif // POINTSLISTMODEL_H
