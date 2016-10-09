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

Item {
    id: root

    property alias header: header.text
    property alias icon: icon.source
    property alias repeaterModel: rep.model
    property alias count: rep.count
    property string contentText
    property bool clickable: false
    property bool list: false

    signal clicked()
    signal modelClicked(int modelId)

    anchors { right: parent.right; left: parent.left }
    height: col.height
    width: (parent ? parent.width : Screen.width)

    Column {
        id: col
        width: parent.width

        Row {
            id: headerRow
            width: parent.width

            Image {
                id: icon
                width: Theme.fontSizeSmall; height: Theme.fontSizeSmall;
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                id: header
                verticalAlignment: Text.AlignVCenter
                width: parent.width - icon.width
                horizontalAlignment: Text.AlignRight
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.highlightColor
            }
        }

        Text {
            text: contentText
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            visible: !clickable && !list
        }

        BackgroundItem {
            id: bgItem
            height: Theme.itemSizeExtraSmall
            anchors.left: parent.left
            anchors.leftMargin: -Theme.horizontalPageMargin
            anchors.right: parent.right
            anchors.rightMargin: -Theme.horizontalPageMargin
            visible: clickable
            Label {
                id: mergedText
                text: contentText
                width: parent.width
                font.pixelSize: Theme.fontSizeSmall
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
                color: bgItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: Theme.horizontalPageMargin
                anchors.rightMargin: Theme.horizontalPageMargin
            }
            onClicked: root.clicked()
        }

        Repeater {
            id: rep
            visible: list
            height: count * Theme.itemSizeExtraSmall
            anchors.left: parent.left
            anchors.right: parent.right
            delegate: BackgroundItem {
                height: Theme.itemSizeExtraSmall
                anchors.left: rep.left
                anchors.leftMargin: -Theme.horizontalPageMargin
                anchors.right: rep.right
                anchors.rightMargin: -Theme.horizontalPageMargin
                Label {
                    id: succOfText
                    width: parent.width
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    //: 1 - the carplate sign, 2 - the district type, 3 - the district name
                    text: qsTr("%1 - %2 %3").arg(model.sign).arg(model.type).arg(model.name)
                    font.pixelSize: Theme.fontSizeSmall
                    color: parent.highlighted ? Theme.highlightColor : Theme.primaryColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.rightMargin: Theme.paddingLarge
                }
                onClicked: root.modelClicked(model.id)
            }
        }
    }
}
