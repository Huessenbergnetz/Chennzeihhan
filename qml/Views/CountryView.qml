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
import "../Delegates"
import "../Common"
import harbour.chennzeihhan 1.0

Page {
    id: countryView
    objectName: "CountryView"

    property string title
    property alias code: countryModel.countryCode
    property var colors: []
    property string sign
    property int type

    onStatusChanged: {
        cc.countryName = countryView.title
        cc.countrySign = countryView.sign
        cc.countryColors = countryView.colors
//        coverConnector.countryName = countryView.title
//        coverConnector.countrySign = countryView.sign
//        coverConnector.countryColors = countryView.colors
    }

    SilicaListView {
        id: listView
        anchors { top: parent.top; left: parent.left; right: parent.right; bottom: type === 1 ? searchField.top : parent.bottom }
        clip: true

        header: PageHeader { width: listView.width; title: countryView.title }

        PullDownMenu {
            visible: countryView.type === 1
            enabled: countryView.type === 1
            MenuItem {
                text: countryModel.searchTarget === Chennzeihhan.Code ? qsTr("Search: Code") : countryModel.searchTarget === Chennzeihhan.Name ? qsTr("Search: Name") : qsTr("Search: Code and Name")
                onClicked: {
                    pageStack.push("../Dialogs/SearchTarget.qml", {cm: countryModel})
                }
            }
            MenuItem {
                id: sorting
                text: countryModel.sortTarget === Chennzeihhan.Code ? qsTr("Sorting: Code") : qsTr("Sorting: Name")
                onClicked: {
                    pageStack.push("../Dialogs/Sorting.qml", {cm: countryModel})
                }
            }
        }

        delegate: CountryDelegate { countryCode: countryModel.countryCode; search: countryModel.search; target: countryModel.searchTarget }

        model: CountryModel { id: countryModel; searchTarget: config.defaultSearchTarget; sortTarget: config.defaultOrderTarget }

        VerticalScrollDecorator {}

        ViewPlaceholder {
            enabled: type === 2
            text: qsTr("Information to the local breakdown of the vehicle registration plate system in %1 will be part of the premium version.").arg(title)
        }

        ViewPlaceholder {
            enabled: type === 0
            text: qsTr("The vehicle registration plate system of %1 does not use a breakdown into districts, regions or something similar. The premium version will contain further information. ").arg(title)
        }
    }

    SearchField {
        id: searchField
        width: parent.width
        anchors { bottom: parent.bottom }
        visible: countryView.type === 1
        placeholderText: qsTr("Search")
        EnterKey.onClicked: searchField.focus = false
        EnterKey.iconSource: "image://theme/icon-m-enter-close"

        Binding {
            target: countryModel
            property: "search"
            value: searchField.text
        }
    }
}
