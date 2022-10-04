import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import DataModels
import QuickChart

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    property real hPos: 0
    property real vPos: 0



    ColumnLayout {
        spacing: 5
        anchors.fill: parent

        RowLayout {
            spacing: 10

            CheckBox {
                text: "Auto scroll X"
                onCheckedChanged: {
                    PointsListModelInstance.autoScrollX = checked
                }
                Component.onCompleted: {
                    PointsListModelInstance.autoScrollX = false
                }
            }

            CheckBox {
                text: "Auto scroll Y"
                onCheckedChanged: {
                    PointsListModelInstance.autoScrollY = checked
                }
                Component.onCompleted: {
                    PointsListModelInstance.autoScrollY = false
                }
            }
        }

        ColumnLayout {
            RowLayout {
                QuickChart {
                    id: quickChart
                    model: PointsListModelInstance
                    Layout.fillWidth: true
                    Layout.fillHeight: true

                    Component.onCompleted: {
                        var ltPoint = PointsListModelInstance.getLeftTopPoint()
                        var rbPoint = PointsListModelInstance.getRightBottomPoint()

                        hPos = ltPoint.x < 0 ? 0.5 : 0
                        vPos = ltPoint.y < 0 ? 0.5 : 0

                        PointsListModelInstance.updateViewPort(width, height, hPos, vPos)
                    }

                    onWidthChanged: {
                        updateScrollBarSize()
                    }

                    onHeightChanged: {
                        updateScrollBarSize()
                    }
                }

                ScrollBar {
                    id: vScroll
                    orientation: Qt.Vertical
                    Layout.fillHeight: true
                    position: vPos

                    onPositionChanged: {
                        PointsListModelInstance.yPosition = position
                    }
                }
            }

            ScrollBar {
                id: hScroll
                orientation: Qt.Horizontal
                position: hPos
                Layout.fillWidth: true

                onPositionChanged: {
                    PointsListModelInstance.xPosition = position
                }
            }
        }
    }

    function updateScrollBarSize() {
        var ltPoint = PointsListModelInstance.getLeftTopPoint()
        var rbPoint = PointsListModelInstance.getRightBottomPoint()

        hScroll.size = width / ((rbPoint.x - ltPoint.x) * (ltPoint.x < 0 ? 2 : 1))
        vScroll.size = height / ((rbPoint.y - ltPoint.y) * (ltPoint.y < 0 ? 2 : 1))
    }

    Connections {
        target: PointsListModelInstance
        function onDataChanged() {
            updateScrollBarSize()
        }
    }

}
