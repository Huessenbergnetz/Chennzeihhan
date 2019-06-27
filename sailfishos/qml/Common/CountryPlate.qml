/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

import QtQuick 2.2
import Sailfish.Silica 1.0

Canvas {
    id: canv
//    renderStrategy: Canvas.Threaded

    property string color: "white"
    property alias text: signText.text
    property var borderColor: ["white"]

    function drawEllipse()
    {
        var ctx = getContext("2d");
        ctx.save();

        if (borderColor.length > 1) {
            var stepSize = 1.0 / borderColor.length
            var step = 0.0
            var gradient = ctx.createLinearGradient(0, 0, 100, 100);
            for (var i = 0; i < borderColor.length; ++i) {
                step += stepSize;
                gradient.addColorStop(step, borderColor[i]);
            }
            ctx.strokeStyle = gradient;
        } else {
            ctx.strokeStyle = borderColor[0];
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

