import QtQuick

import DataModels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    onWidthChanged: {
        PointsListModelInstance.setLeftTopViewPortPoint(0, -height/2)
        PointsListModelInstance.setRightBottomViewPortPoint(width, height/2)
    }

    onHeightChanged: {
        PointsListModelInstance.setLeftTopViewPortPoint(0, -height/2)
        PointsListModelInstance.setRightBottomViewPortPoint(width, height/2)
    }

    Chart {
        id: chart
        model: PointsListModelInstance.filterModel
        anchors.fill: parent
        lineColor: "lime"
        lineWidth: 2.5

    }

    Component.onCompleted: {
        PointsListModelInstance.setLeftTopViewPortPoint(0, -height/2)
        PointsListModelInstance.setRightBottomViewPortPoint(width, height/2)
    }
}
