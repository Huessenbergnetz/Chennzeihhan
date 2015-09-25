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

import QtQuick 2.2
import Sailfish.Silica 1.0

Page {
    id: root
    property int sorting
    property string name

    signal accepted()

    Column {
        anchors.fill: parent
        PageHeader { title: qsTr("Sorting") }

        BackgroundItem {
            width: parent.width
            height: Theme.itemSizeSmall

            Label {
                id: signLabel
                anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin; verticalCenter: parent.verticalCenter }
                text: qsTr("Code")
            }
            onClicked: { sorting = 0; name = signLabel.text; root.accepted(); pageStack.pop() }
        }

        BackgroundItem {
            width: parent.width
            height: Theme.itemSizeSmall

            Label {
                id: nameLabel
                anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin; verticalCenter: parent.verticalCenter }
                text: qsTr("Name")
            }
            onClicked: { sorting = 1; name = signLabel.text; root.accepted(); pageStack.pop() }
        }
    }
}
