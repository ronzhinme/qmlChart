import QtQuick
import QtQuick.Layouts

import DataModels

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Chart {

    }

    ListView {
        id: listView
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        height: 200
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
