import QtQuick 2.0
import Sailfish.Silica 1.0

Canvas {
    id: canv

    property string color: "white"
    property alias text: signText.text
    property string borderColor: "white"

    function createEllipse(ctx, aX, aY, aWidth, aHeight){
        var hB = (aWidth / 2) * .5522848,
            vB = (aHeight / 2) * .5522848,
            eX = aX + aWidth,
            eY = aY + aHeight,
            mX = aX + aWidth / 2,
            mY = aY + aHeight / 2;
        ctx.beginPath();
        ctx.moveTo(aX, mY);
        ctx.bezierCurveTo(aX, mY - vB, mX - hB, aY, mX, aY);
        ctx.bezierCurveTo(mX + hB, aY, eX, mY - vB, eX, mY);
        ctx.bezierCurveTo(eX, mY + vB, mX + hB, eY, mX, eY);
        ctx.bezierCurveTo(mX - hB, eY, aX, mY + vB, aX, mY);
        ctx.closePath();
    }

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

        createEllipse(ctx, 2, 2, width-4, height-4);

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

