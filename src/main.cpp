#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QObject>
#include <QTimer>

#include "model/pointslistmodel.h"

QScopedPointer<PointsListModel> points(new PointsListModel());

void onTimerTriggered()
{
    const auto count = points->rowCount();
    points->insertPoint(count, QPointF(count*8.0, count*(count%2 ? 4.0 : -4.0)));
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // prepare test data
    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, onTimerTriggered);

    //qml register
    points->setAutoScrollX(true);
    qmlRegisterSingletonInstance("DataModels", 1, 0, "PointsListModelInstance", points.get());

    const QUrl url(u"qrc:/qmlChart/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    timer.start(1000);
    return QGuiApplication::exec();
}
