import QtQuick

Canvas {
    property bool isCurve : false

    width: 400
    height: 200
    contextType: "2d"
    renderStrategy: Canvas.Threaded

    Path {
        id: myPath
        startX: 0; startY: 100

        PathLine { x: 75; y: 75 }
        PathLine { x: 200; y: 150 }
        PathLine { x: 325; y: 25 }
        PathLine { x: 370; y: 100 }
        PathLine { x: 400; y: 100 }
    }

    Path {
        id: myPathCurved
        startX: 0; startY: 100

        PathCurve { x: 75; y: 75 }
        PathCurve { x: 200; y: 150 }
        PathCurve { x: 325; y: 25 }
        PathCurve { x: 370; y: 100 }
        PathCurve { x: 400; y: 100 }
    }

    onPaint: {
        context.reset()
        context.lineWidth = 2.3
        context.miterLimit = 1
        context.lineCap = "square"
        context.strokeStyle = Qt.rgba(.4,.6,.8)
        context.path = isCurve ? myPathCurved : myPath
        context.stroke()
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            parent.isCurve = !parent.isCurve
            parent.requestPaint()
        }
    }
}
