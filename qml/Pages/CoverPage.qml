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
import "../Common"

CoverBackground {

    Image {
        source: "/usr/share/harbour-chennzeihhan/images/cover-background.png"
        x: 0; y: 0; z: -1
        opacity: 0.1
        width: parent.width
    }

    CoverPlaceholder {
        visible: cc.mode === CoverConnector.Overview
        text: "Chenn zeihhan"
        icon.source: "/usr/share/icons/hicolor/86x86/apps/harbour-chennzeihhan.png"
    }

    Column {
        id: itemInfo
        visible: cc.mode === CoverConnector.Item || cc.mode === CoverConnector.Wikipedia
        y: Theme.paddingLarge
        anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
        spacing: 0
        Image {
            source: "/usr/share/icons/hicolor/86x86/apps/harbour-chennzeihhan.png"
            width: 86
            height: 86
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.4
            visible: cc.mode !== CoverConnector.Wikipedia
        }
        Image {
            source: "/usr/share/harbour-chennzeihhan/images/wikipedia.png"
            width: 95
            height: 86
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.4
            visible: cc.mode === CoverConnector.Wikipedia
        }
        Label {
            id: sign
            text: cc.sign
            font.pixelSize: Theme.fontSizeHuge
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Label {
            id: name
            visible: text !== "" && state.text !== name.text
            text: cc.name
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }
        Label {
            id: type
            visible: name.text === "" || state.text === name.text
            text: cc.type
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }
        Label {
            id: state
            text: cc.state
            visible: text !== ""
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
        }
        Label {
            id: country
            visible: text !== state.text
            text: cc.country
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
        }
    }

    Item {
        id: countryInfo
        visible: cc.mode === CoverConnector.Country
        anchors.fill: parent
        CountryPlate {
            y: Theme.paddingLarge
            width: 140; height: 90
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            borderColor: cc.countryColors
            text: cc.countrySign
            onBorderColorChanged: requestPaint()
            smooth: true
        }
        Label {
            text: cc.countryName
            width: parent.width - 2* Theme.paddingLarge
            color: Theme.secondaryColor
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
        }
    }

    CoverActionList {
        enabled: pageStack.depth > 1
        CoverAction {
            iconSource: "image://theme/icon-cover-previous"
            onTriggered: pageStack.navigateBack(PageStackAction.Immediate)
        }
    }
}


