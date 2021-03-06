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

Page {
    id: chItemView
    objectName: "ItemView"

    property alias sign: pHeader.title
    property alias name: nameLabel.text
    property alias capital: capitalText.contentText
    property alias capitalHeader: capitalText.header
    property string wikipedia
    property string wikipediaLang

    function attachWikipedia() {
        if (status == PageStatus.Active) {
            if (wikipedia !== "") {
                pageStack.pushAttached(Qt.resolvedUrl("ItemWebView.qml"), {wpLang: wikipediaLang, wpName: wikipedia})
            } else {
                if (forwardNavigation) {
                    pageStack.popAttached()
                }
            }
        }
    }

    onStatusChanged: {
        attachWikipedia()
    }

    onWikipediaChanged: {
        attachWikipedia()
    }

    SilicaFlickable {
        id: singleItem
        PageHeader { id: pHeader }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: headerCol.height + contentCol.height + Theme.paddingLarge


        Column {
            id: headerCol
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            Label {
                id: nameLabel
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
