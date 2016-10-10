/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2016  Buschtrommel/Matthias Fehring

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
    id: root
    objectName: "ItemView"

    property alias sign: pHeader.title
    property alias name: nameLabel.text
    property alias state: stateLabel.text
    property alias capital: capitalText.contentText
    property int disbanded: 0
    property int founded: 0
    property int optional: 0
    property alias optionalSigns: optSignsText.contentText
    property alias antecessors: antecessorsList.repeaterModel
    property alias successor: mergedText.contentText
    property int successorId: 0
    property alias tpo: todayPartOfText.contentText
    property int tpoId: 0
    property bool inOperation

    property string wikipedia
    property string wikipediaLang

    signal successorClicked(int succId)
    signal tpoClicked(int tpoId)
    signal antecessorClicked(int anteId)

    onStatusChanged: {
        if (status == PageStatus.Active && wikipedia !== "") {
            pageStack.pushAttached(Qt.resolvedUrl("ItemWebView.qml"), {wpLang: wikipediaLang, wpName: wikipedia})
        }
    }

    BusyIndicator {
        visible: inOperation
        running: visible
        size: BusyIndicatorSize.Large
        anchors.centerIn: parent
    }

    SilicaFlickable {
        id: singleItem
        PageHeader { id: pHeader }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: headerCol.height + contentCol.height + listCol.height + Theme.paddingLarge

        Column {
            id: headerCol
            visible: !inOperation
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }

            Label {
                id: nameLabel
                textFormat: Text.PlainText
                color: Theme.highlightColor
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Label {
                id: stateLabel
                textFormat: Text.PlainText
                color: Theme.highlightColor
            }
        }


        Column {
            id: contentCol
            anchors { top: headerCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            spacing:Theme.paddingLarge
            visible: !inOperation

            ItemEntry {
                id: capitalText
                header: qsTr("Capital")
                icon: "image://theme/icon-s-task"
            }

            ItemEntry {
                id: existenceText
                header: disbanded === 0 ? qsTr("Existing since") : qsTr("Existed from")
                contentText: disbanded === 0 ? founded : founded + " - " + disbanded
                icon: "image://theme/icon-s-date"
            }

            ItemEntry {
                id: optSignsText
                header: qsTr("Optional plate signs")
                visible: contentText !== ""
                icon: "image://theme/icon-l-share"
            }

            ItemEntry {
                id: optionalText
                header: qsTr("Sign optional available since")
                visible: optional
                icon: "image://theme/icon-m-refresh"
                contentText: optional
            }
        }

        Column {
            id: listCol
            anchors { top: contentCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.horizontalPageMargin; rightMargin: Theme.horizontalPageMargin }
            visible: !inOperation

            ItemEntry {
                id: mergedText
                header: qsTr("Merged into")
                visible: successorId !== 0
                icon: "image://theme/icon-s-device-upload"
                clickable: true
                onClicked: root.successorClicked(successorId)
            }

            ItemEntry {
                id: todayPartOfText
                header: qsTr("Today part of")
                visible: tpoId !== 0 && tpoId !== successorId
                icon: "image://theme/icon-m-location"
                clickable: true
                onClicked: root.tpoClicked(tpoId)
            }

            ItemEntry {
                id: antecessorsList
                header: qsTr("Includes this old districts")
                visible: count > 0
                icon: "image://theme/icon-m-levels"
                list: true
                onModelClicked: root.antecessorClicked(modelId)
            }
        }
    }
}
