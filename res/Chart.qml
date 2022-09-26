import QtQuick

Canvas {
    property bool isCurve: false
    property var model: undefined
    property color lineColor: Qt.rgba(0,0,0)
    property real lineWidth: 1
    property bool isYCentred : true

    contextType: "2d"
    renderStrategy: Canvas.Threaded

    onPaint: {
        context.reset()
        context.lineWidth = lineWidth
        context.strokeStyle = lineColor

        for( var i = 0; i < model.rowCount(); i++ ) {
            var point = model.getPoint(i)
            point.y = point.y + (isYCentred ? height / 2: 0)
            if(i === 0) {
                context.moveTo(point.x, point.y)
            }

            context.lineTo(point.x, point.y)
        }

        context.stroke()
        console.log("======== done ! ===========")
    }
}
