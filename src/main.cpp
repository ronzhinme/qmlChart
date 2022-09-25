#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "model/pointslistmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    //qml register
    QScopedPointer<PointsListModel> points(new PointsListModel());
    qmlRegisterSingletonInstance("DataModels", 1, 0, "PointsListModelInstance", points.get());

    std::srand(std::time(nullptr)); // use current time as seed for random generator
    for(auto i = 0; i < 100000; ++i)
    {
        points->insertPoint(points->rowCount(), QPointF(std::rand(), std::rand()));
    }

    const QUrl url(u"qrc:/qmlChart/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
