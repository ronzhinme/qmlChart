import QtQuick

import DataModels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    onWidthChanged: {
        PointsListModelInstance.setLeftTopViewPortPoint(0, 0)
        PointsListModelInstance.setRightBottomViewPortPoint(width, height)
    }

    onHeightChanged: {
        PointsListModelInstance.setLeftTopViewPortPoint(0, 0)
        PointsListModelInstance.setRightBottomViewPortPoint(width, height)
    }

    Flickable {
        anchors.fill: parent

        Chart {
            model: PointsListFilterInstance
            anchors.fill: parent
            lineColor: "lime"
            lineWidth: 2.5
        }        
    }

    Component.onCompleted: {
        PointsListModelInstance.setLeftTopViewPortPoint(0, 0)
        PointsListModelInstance.setRightBottomViewPortPoint(width, height)
    }
}
