import QtQuick
import QtQuick.Controls

import DataModels
import QuickChart

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    QuickChart {
        anchors.fill: parent
        model: PointsListModelInstance
    }
}
