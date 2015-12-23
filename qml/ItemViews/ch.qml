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
    id: chItemView
    objectName: "ItemView"

    property int itemId

    property string countryCode: "ch"

    property string sign
    property string name
    property string capital
    property string wikipedia

    function getItemData()
    {
        var itemData = itemModel.getItemData(countryCode, itemId);
        sign = itemData["sign"];
        name = itemData["name"];
        capitalText.contentText = itemData["capital"];
        wikipedia = itemData["wikipedia"];
    }

    Component.onCompleted: {
        getItemData()
    }

    onStatusChanged: {
        coverConnector.country = qsTr("Switzerland")
        coverConnector.state = ""
        coverConnector.name = chItemView.name
        coverConnector.sign = chItemView.sign
        if (status == PageStatus.Active && wikipedia !== "") {
            pageStack.pushAttached(Qt.resolvedUrl("ItemWebView.qml"), {wpLang: "de", wpName: wikipedia})
        }
    }

    SilicaFlickable {
        id: singleItem
        PageHeader { title: sign }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: headerCol.height + contentCol.height + Theme.paddingLarge


        Column {
            id: headerCol
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            Label {
                id: nameLabel
                text: qsTr("Canton %2").arg(name)
                textFormat: Text.PlainText
                color: Theme.highlightColor
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

        }


        Column {
            id: contentCol
            anchors { top: headerCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            spacing:Theme.paddingLarge

            ItemEntry {
                id: capitalText
                header: qsTr("Capital")
                icon: "image://theme/icon-s-task"
            }
        }
    }
}
