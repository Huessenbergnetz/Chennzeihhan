/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2016  Buschtrommel/Matthias Fehring

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
import "Views"

ApplicationWindow
{
    id: chennzeihhan

    property bool inOperation: false

    function getCoverMode() {
        switch(pageStack.currentPage.objectName) {
        case "ItemView":
            return CoverConnector.Item
        case "CountryView":
            return CoverConnector.Country
        case "WikiView":
            return CoverConnector.Wikipedia
        default:
            return CoverConnector.Overview
        }
    }

    Connections {
        target: config
        onFavsChanged: inOperation = false
    }

    initialPage: Component { MainView { } }
    cover: Qt.resolvedUrl("Pages/CoverPage.qml")

    Connections {
        target: pageStack
        onCurrentPageChanged: cc.mode = getCoverMode()
    }
}


