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
import harbour.chennzeihhan 1.0

Page {
    id: deItemView
    objectName: "ItemView"

    DeItem {
        id: deItem
    }

    property alias itemId: deItem.id

    onStatusChanged: {
        if (status == PageStatus.Active && deItem.wikipedia !== "") {
            pageStack.pushAttached(Qt.resolvedUrl("ItemWebView.qml"), {wpLang: "de", wpName: deItem.wikipedia})
        }
        coverConnector.country = qsTr("Germany")
        coverConnector.name = deItem.name
        coverConnector.sign = deItem.sign
        coverConnector.type = deItem.type
        coverConnector.state = deItem.state
    }

    BusyIndicator {
        visible: deItem.inOperation
        running: visible
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
    }

    SilicaFlickable {
        id: singleItem
        PageHeader { id: pHeader; title: deItem.sign }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: headerCol.height + contentCol.height + listCol.height + Theme.paddingLarge

        Column {
            id: headerCol
            visible: !deItem.inOperation
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }

            Label {
                id: nameLabel
                text: qsTr("%1 %2").arg(deItem.type).arg(deItem.name)
                textFormat: Text.PlainText
                color: Theme.highlightColor
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Label {
                id: stateLabel
                textFormat: Text.PlainText
                color: Theme.highlightColor
                text: deItem.state
            }
        }


        Column {
            id: contentCol
            anchors { top: headerCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            spacing:Theme.paddingLarge
            visible: !deItem.inOperation

            ItemEntry {
                id: capitalText
                header: qsTr("Capital")
                icon: "image://theme/icon-s-task"
                contentText: deItem.capital
            }

            ItemEntry {
                id: existenceText
                header: deItem.disbanded === 0 ? qsTr("Existing since") : qsTr("Existed from")
                contentText: deItem.disbanded === 0 ? deItem.founded : deItem.founded + " - " + deItem.disbanded
                icon: "image://theme/icon-s-date"
            }

            ItemEntry {
                id: optSignsText
                header: qsTr("Optional plate signs")
                visible: deItem.optionalSigns !== ""
                icon: "image://theme/icon-l-share"
                contentText: deItem.optionalSigns
            }

            ItemEntry {
                id: optionalText
                header: qsTr("Sign optional available since")
                visible: deItem.optional
                icon: "image://theme/icon-m-refresh"
                contentText: deItem.optional
            }
        }

        Column {
            id: listCol
            anchors { top: contentCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            visible: !deItem.inOperation

            ItemEntry {
                id: mergedText
                header: qsTr("Merged into")
                visible: deItem.successorId !== 0
                icon: "image://theme/icon-s-device-upload"
                contentText: deItem.successor
                clickable: true
                onClicked: deItem.id = deItem.successorId
            }

            ItemEntry {
                id: todayPartOfText
                header: qsTr("Today part of")
                visible: deItem.tpoId !== 0 && deItem.tpoId !== deItem.successorId
                icon: "image://theme/icon-m-location"
                contentText: deItem.tpo
                clickable: true
                onClicked: deItem.id = deItem.tpoId
            }

            ItemEntry {
                id: antecessors
                header: qsTr("Includes this old districts")
                visible: count > 0
                icon: "image://theme/icon-m-levels"
                repeaterModel: deItem.antecessors
                list: true
                onModelClicked: deItem.id = modelId
            }
        }
    }
}
