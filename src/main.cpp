#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "model/pointslistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    // prepare test data
    QScopedPointer<PointsListModel> points(new PointsListModel());
    for(auto i = 0; i < 1000; ++i)
    {
        points->insertPoint(points->rowCount(), QPointF(i*4.0, i/(i%2 ? 10.0 : -10.0)));
    }

    //qml register
    qmlRegisterSingletonInstance("DataModels", 1, 0, "PointsListModelInstance", points.get());

    const QUrl url(u"qrc:/qmlChart/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
