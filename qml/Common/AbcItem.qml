/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

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

import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property string text
    property bool showBg
    width: 108; height: 108
    highlightedColor: "transparent"

    Image {
        z: 0
        anchors.fill: parent
        fillMode: Image.Tile
        visible: showBg && !root.pressed
        source: "/usr/share/harbour-chennzeihhan/images/abcbg.png"
    }

    Label {
        z: 1
        id: label
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: Theme.fontSizeExtraLarge
        color: showBg && !root.pressed ? Theme.primaryColor : Theme.highlightColor
        opacity: 0.7
    }
}
