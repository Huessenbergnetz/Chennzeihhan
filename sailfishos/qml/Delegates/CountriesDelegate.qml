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
import "../Common"
import harbour.chennzeihhan 1.0

ListItem {
    id: listItem

    property alias showBg: bgImage.visible
    property bool fav: favoritesModel.isFav(model.sign)
    property string search
    property int target

    property string name: (countriesModel.searchTarget === 1 || countriesModel.searchTarget === 2) ? Theme.highlightText(model.name, countriesModel.search, Theme.highlightColor) : model.name
    property string sign: (countriesModel.searchTarget === 0 || countriesModel.searchTarget === 2) ? Theme.highlightText(model.sign, countriesModel.search, Theme.secondaryHighlightColor) : model.sign

    onClicked: pageStack.push(Qt.resolvedUrl("../Views/CountryView.qml"), {title: model.name, code: model.code, type: model.type, colors: model.colors, sign: model.sign})

    onPressAndHold: if (fav) { rmFav() } else { favoritesModel.add(model.sign); fav = true }

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight
    contentHeight: GridView.view.cellHeight

    GridView.onAdd: AddAnimation { target: listItem }
    GridView.onRemove: RemoveAnimation { target: listItem }

    Connections {
        target: favoritesModel
        onModelChanged: listItem.fav = favoritesModel.isFav(model.sign)
    }

    Image {
        id: bgImage
        z: 0
        anchors.fill: parent
        source: "/usr/share/harbour-chennzeihhan/images/country-background.png"
    }

    Image {
        id: favIcon
        z: 1
        anchors { top: parent.top; topMargin: Theme.paddingSmall; left: parent.left; leftMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-favorite"
        opacity: fav ? 1 : 0
        width: 26; height: 26
        Behavior on opacity { FadeAnimation {} }
    }

    CountryPlate {
        id: plate
        z: 1
        width: 140; height: 90
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 15 }
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        borderColor: model.colors ? model.colors : "white"
        text: sign
    }

    Image {
        id: official
        z: 1
        anchors { bottom: itemTitle.top; bottomMargin: Theme.paddingSmall; left: parent.left; leftMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-installed"
        visible: model.official
        width: 26; height: 26
    }

    Image {
        id: list
        z: 1
        anchors { bottom: itemTitle.top; bottomMargin: Theme.paddingSmall; right: parent.right; rightMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-group-chat"
        visible: model.type > 0
        width: 26; height: 26
    }

    Label {
        id: itemTitle
        z: 1
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; leftMargin: Theme.paddingMedium; right: parent.right; rightMargin: Theme.paddingMedium }
        text: name
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        maximumLineCount: 1
        font.pixelSize: Theme.fontSizeTiny
        truncationMode: TruncationMode.Fade
        textFormat: Text.RichText
        width: parent.width - Theme.paddingLarge
    }

    function rmFav() {
        remorse.execute(listItem, qsTr("Romving from favourites"), function() {favoritesModel.remove(model.sign); fav = false }, 3000)
    }

    RemorseItem { id: remorse }

}
