import QtQuick
import QtQuick.Controls

import DataModels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Chart {
        id: chart
        model: PointsListModelInstance.filterModel
        anchors.fill: parent
        lineColor: "orange"
        lineWidth: 2.5
        minX: PointsListModelInstance.getLeftTopPoint().x
        maxX: PointsListModelInstance.getRightBottomPoint().x
        minY: PointsListModelInstance.getLeftTopPoint().y
        maxY: PointsListModelInstance.getRightBottomPoint().y

        onYPositionOffsetChanged: {
            updateViewPort()
        }

        onXPositionOffsetChanged: {
            updateViewPort()
        }

        function updateViewPort() {
            let x = chart.maxX * xPositionOffset
            let y = chart.maxY * yPositionOffset

            PointsListModelInstance.setLeftTopViewPortPoint(x, y)
            PointsListModelInstance.setRightBottomViewPortPoint(x + chart.width, y + chart.height)

            console.log("LT:",PointsListModelInstance.getLeftTopViewPortPoint().x, PointsListModelInstance.getLeftTopViewPortPoint().y);
            console.log("RB:",PointsListModelInstance.getRightBottomViewPortPoint().x, PointsListModelInstance.getRightBottomViewPortPoint().y);
        }

        onWidthChanged: {
            updateViewPort()
        }

        onHeightChanged: {
            updateViewPort()
        }

        Component.onCompleted: {
            updateViewPort()
        }
    }
}
