import QtQuick 2.0
import Sailfish.Silica 1.0

Canvas {
    id: canv
    renderStrategy: Canvas.Threaded

    property string color: "white"
    property alias text: signText.text
    property string borderColor: "white"

    function drawEllipse()
    {
        var ctx = getContext("2d");
        ctx.save();

        var colors = borderColor.split(",")

        if (colors.length > 1) {
            var stepSize = 1.0 / colors.length
            var step = 0.0
            var gradient = ctx.createLinearGradient(0, 0, 100, 100);
            for (var i = 0; i < colors.length; ++i) {
                step += stepSize;
                gradient.addColorStop(step, colors[i]);
            }
            ctx.strokeStyle = gradient;
        } else {
            ctx.strokeStyle = colors[0];
        }

        ctx.lineWidth = 4;

        ctx.ellipse(2, 2, width-4, height-4);

        ctx.stroke();
    }

    onPaint: drawEllipse()


    Text {
        id: signText
        anchors.centerIn: parent
        color: canv.color
        font.bold: true
        font.pixelSize: 50
        style: Text.RichText
    }
}

