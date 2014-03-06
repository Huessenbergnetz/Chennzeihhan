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

Item  {
    id: root
    width: parent.width
    height: 108
    property variant cont
    property string cha

    signal clicked(string txt)

    Component.onCompleted: listModel.fill()

    Row {
        height: parent.height
        anchors { left: parent.left; right: parent.right }
        Repeater {
            height: root.height
            model: listModel
            delegate: AbcItem {
                text: model.text
                showBg: root.cha !== text
                onClicked: root.clicked(text)
            }
        }
    }

    ListModel {
        id: listModel
        property variant characters: cont

        function fill() {
            for (var index = 0; index < characters.length; index++) {
                append({ "text": characters[index] })
            }
        }
    }
}
