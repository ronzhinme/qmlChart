import QtQuick

import DataModels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Flickable {
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.verticalCenter

        Chart {
            model: PointsListModelInstance
            anchors.fill: parent
            lineColor: "lime"
            lineWidth: 2.5
        }
    }

    ListView {
        id: listView
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.verticalCenter
        model: PointsListModelInstance
        delegate: Text {
            text: index + "\tx: " + display.x + "\ty: " + display.y
        }
        clip: true
    }

    Rectangle {
        color: "transparent"
        border.color: "black"
        border.width: 1
        anchors.fill: listView
    }
}
