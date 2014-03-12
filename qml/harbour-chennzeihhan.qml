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
import "Views"

ApplicationWindow
{
    id: chennzeihhan

    property bool dataBaseExists: dbMan.checkDB()
    property int installedDbRevision: dlMan.getLocalDBVersion()
    property int minimumDbRevision: 8
    property bool inOperation: false


    function getCoverMode() {
        switch(pageStack.currentPage.objectName) {
        case "ItemView":
            return "item";
        case "CountryView":
            return "country"
        case "WikiView":
            return "wikipedia"
        default:
            return "overview"
        }
    }

    Connections {
        target: dlMan
        onDbDownloadFinished: { checkDbTimer.start(); installedDbRevision = dlMan.getLocalDBVersion() }
    }

    Connections {
        target: config
        onFavsChanged: inOperation = false
    }

    Timer {
        id: checkDbTimer; interval: 200; running: false; repeat: false
        onTriggered: { dataBaseExists = dbMan.checkDB() }
    }

    initialPage: Component { MainView { } }
    cover: Qt.resolvedUrl("Pages/CoverPage.qml")

    QtObject {
        id: coverConnector

        property string country
        property string name
        property string type
        property string sign
        property string state
        property string colors
        property string countryName
        property string countrySign
        property string countryColors
        property string mode: "overview"
    }


    Connections {
        target: pageStack
        onCurrentPageChanged: coverConnector.mode = getCoverMode()
    }
}


