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

ListItem {
    id: listItem

    property string countryCode
    property string search
    property int target

    property string name: (target === 1 || target === 2) ? Theme.highlightText(model.name, search, Theme.highlightColor) : model.name
    property string sign: (target === 0 || target === 2) ? Theme.highlightText(model.sign, search, Theme.secondaryHighlightColor) : model.sign

    contentHeight: Theme.itemSizeMedium

    onClicked: pageStack.push(Qt.resolvedUrl("../ItemViews/"+ countryCode + ".qml"), {itemId: model.itemId})

    ListView.onAdd: AddAnimation { target: listItem }

    ListView.onRemove: RemoveAnimation { target: listItem }

    Row {

        id: mainRow
        anchors.fill: parent
        anchors.leftMargin: Theme.paddingLarge
        anchors.rightMargin: Theme.paddingLarge
        spacing: 8

//        Image {
//            id: coa
//            source: "/usr/share/harbour-chennzeihhan/images/" + listItem.countryCode + "/" + model.sign + "_small.png"
//            sourceSize.width: 64
//            width: 64
//        }

        Column {
//            width: parent.width - coa.width
            width: parent.width

            Label {
                id: itemTitle
                text: qsTr("%1 %2").arg(model.type).arg(name)
                color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                maximumLineCount: 1
                truncationMode: TruncationMode.Fade
                textFormat: Text.RichText
                width: parent.width
            }

            Row {
                width: parent.width

                Text {
                    text: model.state ? qsTr("%1 - %2").arg(sign).arg(model.state) : sign
                    color: listItem.highlighted ? Theme.secondaryHighlightColor : Theme.secondaryColor
                    textFormat: Text.RichText
                    font.pixelSize: Theme.fontSizeSmall
                    width: parent.width - closedIcon.width
                }

                Image {
                    id: closedIcon
                    visible: model.closed
                    width: Theme.fontSizeSmall; height: Theme.fontSizeSmall
                    source: "image://theme/icon-s-timer"
                }
            }
        }
    }
}
