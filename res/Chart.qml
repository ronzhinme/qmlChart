import QtQuick
import QtQuick.Controls

Item {
    property real minX: 0.0
    property real maxX: 1.0
    property real minY: 0.0
    property real maxY: 1.0

    property alias yPositionOffset: vScrollBar.position
    property alias xPositionOffset: hScrollBar.position

    property var model: undefined
    property color lineColor: Qt.rgba(0,0,0)
    property real lineWidth: 1

    property bool isYZeroCentered : true
    property bool isXZeroCentered : false

    onYPositionOffsetChanged: {
        canvas.requestPaint()
    }

    onXPositionOffsetChanged: {
        canvas.requestPaint()
    }

    Canvas {
        id: canvas
        contextType: "2d"
        renderStrategy: Canvas.Threaded
        anchors.left: parent.left
        anchors.right: vScrollBar.left
        anchors.top: parent.top
        anchors.bottom: hScrollBar.top

        onPaint: {
            busyIndicator.running = true
            context.reset()
            context.lineWidth = parent.lineWidth
            context.strokeStyle = parent.lineColor

            for( var i = 0; i < parent.model.rowCount(); i++ ) {
                var index = parent.model.index(i,0)
                var point = parent.model.data(index);

                point.y = point.y
                        + (isYZeroCentered ? (canvas.height / 2) : 0)
                        - (maxY * vScrollBar.position)
                point.x = point.x
                        + (isXZeroCentered ? (canvas.width / 2) : 0)
                        - (maxX * hScrollBar.position)

                if(i === 0) {
                    context.moveTo(point.x, point.y)
                }

                context.lineTo(point.x, point.y)
            }

            context.stroke()
            console.log("done!");
        }

        onPainted: {
            busyIndicator.running = false
        }

        BusyIndicator {
            id: busyIndicator
            anchors.centerIn: parent
            running: false
        }

        onWidthChanged: {
           hScrollBar.size = canvas.width / ((maxX-minX) * (isXZeroCentered ? 2 : 1))
        }

        onHeightChanged: {
            vScrollBar.size = canvas.height/((maxY-minY) * (isYZeroCentered ? 2 : 1))
        }
    }

    ScrollBar {
        id: vScrollBar
        orientation: Qt.Vertical
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: hScrollBar.top
    }

    ScrollBar {
        id: hScrollBar
        orientation: Qt.Horizontal
        anchors.right: vScrollBar.left
        anchors.left: parent.left
        anchors.bottom: parent.bottom
    }
}
