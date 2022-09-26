import QtQuick

Canvas {
    property bool isCurve: false
    property var model: undefined
    property color lineColor: Qt.rgba(0,0,0)
    property real lineWidth: 1

    contextType: "2d"
    renderStrategy: Canvas.Threaded

    onPaint: {
        context.reset()
        context.lineWidth = lineWidth
        context.strokeStyle = lineColor

        for( var i = 0; i < model.rowCount(); i++ ) {
            var point = model.getPoint(i)
            if(i === 0) {
                context.moveTo(point.x, point.y)
            }

            context.lineTo(point.x, point.y)
        }

        context.stroke()
    }
}
