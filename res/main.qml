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
        anchors.fill: parent

        ColumnLayout {

        RowLayout {

            TextField {
                id: minXLimit
                horizontalAlignment: Text.AlignHCenter
                placeholderText: "Min X "
                validator: DoubleValidator {decimals: 2}
                onEditingFinished: {
                    PointsListModelInstance.axisXLimitEnabled = (maxXLimit.text != "" || minXLimit.text != "")
                    PointsListModelInstance.axisXLimitMin = parseFloat(text)
                }
            }

            TextField {
                id: maxXLimit
                horizontalAlignment: Text.AlignHCenter
                placeholderText: "Max X "
                validator: DoubleValidator {decimals: 2}
                onEditingFinished: {
                    PointsListModelInstance.axisXLimitEnabled = (maxXLimit.text != "" || minXLimit.text != "")
                    PointsListModelInstance.axisXLimitMax = parseFloat(text)
                }
            }
        }

        RowLayout {

            TextField {
                id: minYLimit
                horizontalAlignment: Text.AlignHCenter
                placeholderText: "Min Y "
                validator: DoubleValidator {decimals: 2}
                onEditingFinished: {
                    PointsListModelInstance.axisYLimitEnabled = (maxYLimit.text != "" || minYLimit.text != "")
                    PointsListModelInstance.axisYLimitMax = parseFloat(text)
                }
            }

            TextField {
                id: maxYLimit
                horizontalAlignment: Text.AlignHCenter
                placeholderText: "Max Y "
                validator: DoubleValidator {decimals: 2}
                onEditingFinished: {
                    PointsListModelInstance.axisYLimitEnabled = (maxYLimit.text != "" || minYLimit.text != "")
                    PointsListModelInstance.axisYLimitMax = parseFloat(text)
                }
            }
        }

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

            TextField {
                horizontalAlignment: Text.AlignHCenter
                text: "1.0"
                validator: DoubleValidator{bottom: -5; top: 5}
                onEditingFinished: {
                    PointsListModelInstance.scaleRatioX = parseFloat(text)
                    PointsListModelInstance.scaleRatioY = parseFloat(text)
                }
            }
        }
}

        ColumnLayout {
            RowLayout {
                QuickChart {
                    id: quickChart
                    model: PointsListModelInstance
                    clip: true
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

                    Rectangle {
                        anchors.fill: parent
                        color:"transparent"
                        border.color:"gray"
                        border.width: 1
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
        var scaleX = PointsListModelInstance.scaleRatioX
        var scaleY = PointsListModelInstance.scaleRatioY

        hScroll.size = width / ((rbPoint.x - ltPoint.x) * (ltPoint.x < 0 ? 2 : 1)) * scaleX
        vScroll.size = height / ((rbPoint.y - ltPoint.y) * (ltPoint.y < 0 ? 2 : 1)) * scaleY
    }

    Connections {
        target: PointsListModelInstance
        function onDataChanged() {
            updateScrollBarSize()
        }
    }

}
