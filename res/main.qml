import QtQuick
import QtQuick.Controls

import DataModels
import QuickChart

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    //    Chart {
    //        id: chart
    //        model: PointsListModelInstance.filterModel
    //        anchors.fill: parent
    //        lineColor: "orange"
    //        lineWidth: 2.5
    //        minX: PointsListModelInstance.getLeftTopPoint().x
    //        maxX: PointsListModelInstance.getRightBottomPoint().x
    //        minY: PointsListModelInstance.getLeftTopPoint().y
    //        maxY: PointsListModelInstance.getRightBottomPoint().y

    //        onYPositionOffsetChanged: {
    //            updateViewPort()
    //        }

    //        onXPositionOffsetChanged: {
    //            updateViewPort()
    //        }

    //        function updateViewPort() {
    //            let x = chart.isXZeroCentered ? (2 * chart.maxX * xPositionOffset - chart.maxX)
    //                                          : chart.maxX * xPositionOffset
    //            let y = chart.isYZeroCentered ? (2 * chart.maxY * yPositionOffset - chart.maxY)
    //                                          : chart.maxY * yPositionOffset
    //            let x1 = x + chart.width
    //            let y1 = y + chart.height

    //            PointsListModelInstance.setLeftTopViewPortPoint(x, y)
    //            PointsListModelInstance.setRightBottomViewPortPoint(x1, y1)

    ////            console.log("LT:",PointsListModelInstance.getLeftTopViewPortPoint().x, PointsListModelInstance.getLeftTopViewPortPoint().y);
    ////            console.log("RB:",PointsListModelInstance.getRightBottomViewPortPoint().x, PointsListModelInstance.getRightBottomViewPortPoint().y);
    //        }

    //        onWidthChanged: {
    //            updateViewPort()
    //        }

    //        onHeightChanged: {
    //            updateViewPort()
    //        }

    //        Component.onCompleted: {
    //            updateViewPort()
    //        }
    //    }

    QuickChart {
        anchors.fill: parent
        model: PointsListModelInstance
    }
}
