import QtQuick
import QtQuick.Controls

import DataModels
import QuickChart

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property real hPos: 0
    property real vPos: 0

    QuickChart {
        id: quickChart
        anchors.fill: parent
        model: PointsListModelInstance
        anchors.bottom: hScroll.top
        anchors.right: vScroll.left
        anchors.top: parent.top
        anchors.left: parent.left

        Component.onCompleted: {
            var ltPoint = PointsListModelInstance.getLeftTopPoint()
            hPos = ltPoint.x < 0 ? 0.5 : 0
            vPos = ltPoint.y < 0 ? 0.5 : 0

            PointsListModelInstance.updateViewPort(width
                                                   , height
                                                   , hPos
                                                   , vPos)
        }
    }

    ScrollBar {
        id: hScroll
        orientation: Qt.Horizontal
        anchors.left: parent.left
        anchors.right: vScroll.left
        anchors.bottom: parent.bottom
        position: hPos

        onPositionChanged: {
            PointsListModelInstance.xPosition = position
        }
    }

    ScrollBar {
        id: vScroll
        orientation: Qt.Vertical
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        position: vPos

        onPositionChanged: {
            PointsListModelInstance.yPosition = position
        }
    }

}
