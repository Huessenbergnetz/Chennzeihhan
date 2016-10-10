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
import "../Delegates"
import "../Common"
import "../BTComponents"
import "../Models"
import harbour.chennzeihhan 1.0

Page {
    id: mainView
    objectName: "MainView"

    property string searchString
    property int searchTarget: config.defaultSearchTarget
    property int sortType: config.defaultOrderTarget
    property string cha: ""
    property int activeRow: 0
    property bool showMainContent: dbMan.dbExists && (config.databaseVersion >= config.minimumDbVersion) && searchString === ""
    property variant abc
    readonly property int abcColumns: 5
    readonly property real plateRatio: 0.84

    FirstStartInfo {
        visible: config.get("system/version", 0) < versionInt
        name: "Chennzeihhan"
        version: versionString
        helpPage: "../Pages/Help.qml"
        description: qsTr("Chennzeihhan (old high german for Kennzeichen/registration plate) is an offline database for vehicle registration plates that can find the district of the vehicle plate. It covers currently more than 1200 international and local codes from Austria, Germany and Switzerland.")
        changeLogModel: ChangelogModel {}
        changeLogTracker: "https://github.com/Buschtrommel/Chennzeihhan/issues/"
        onClicked: config.set("system/version", versionInt)
    }

    Connections {
        target: config
        onDefaultSearchTargetChanged: { searchTarget = defaultSearchTarget; searchT.currentIndex = searchTarget }
        onDefaultOrderTargetChanged: { sortType = defaultOrderTarget; sortOrdering.currentIndex = sortType }
    }

    onSearchStringChanged: countriesSearch.refresh(searchString, searchTarget, sortType)
    onSortTypeChanged: { alphabetModel.init(sortType); if (cha !== "") { countriesModel.setFirstChar(cha, sortType) } else if (searchString !== "") { countriesSearch.refresh(searchString, searchTarget, sortType) } }
    onSearchTargetChanged: if (searchString !== "") countriesSearch.refresh(searchString, searchTarget, sortType)
    onChaChanged: countriesModel.setFirstChar(cha, sortType)

    SilicaFlickable {
        id: flick
        anchors.fill: parent
        VerticalScrollDecorator {}
        interactive: searchString === ""
        contentHeight: contentCol.height
        clip: true

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/About.qml"))
            }
            MenuItem {
                text: qsTr("Help/Legend")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Help.qml"))
            }
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))
            }
        }


        Column {
            id: contentCol
            anchors { left: parent.left; right: parent.right }
            move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
            add: Transition { AddAnimation {} }
            PageHeader { id: pageHeader; title: "Chennzeihhan" }
            Behavior on height {
                        NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
                    }

            SearchField {
                id: searchField
                visible: dbMan.dbExists && (config.databaseVersion >= config.minimumDbVersion)
                anchors { left: parent.left; right: parent.right; }
                placeholderText: qsTr("Search ...")
                EnterKey.onClicked: searchField.focus = false
                EnterKey.iconSource: "image://theme/icon-m-enter-close"

                Binding {
                    target: mainView
                    property: "searchString"
                    value: searchField.text
                }
            }

            GridView {
                id: favourites
                visible: count > 0 && showMainContent
                height: visible ? Math.ceil(count / 3) * cellHeight : 0
                anchors { left: parent.left; right: parent.right }
                delegate: CountriesDelegate{ showBg: false}
                interactive: false
                cellWidth: width/3; cellHeight: cellWidth * plateRatio
                model: countriesFavourites
                Component.onCompleted: countriesFavourites.getFavs()
                Connections {
                    target: config
                    onFavsChanged: countriesFavourites.getFavs()
                }
            }

            Item {
                height: Theme.paddingLarge
                width: parent.width
                visible: favourites.visible
            }

            Item {
                id: abcGrid
                visible: showMainContent
                anchors { left: parent.left; right: parent.right }

                property real cellWidth: width/abcColumns
                property real cellHeight: width/abcColumns

                height: col.height

                Column {
                    id: col
                    anchors { left: parent.left; right: parent.right }
                    move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
                    add: Transition { AddAnimation {} }
                    Repeater {
                        model: AlphabetModel { id: alphabetModel; dbManager: dbMan }

                        Item {
                            id: rowBase
                            anchors { left: parent.left; right: parent.right }
                            height: abcRow.height + grid.height
                            property int rowIdx: model.index

                            Row {
                                id: abcRow
                                z: 2
                                Repeater {
                                    model: row

                                    BackgroundItem {
                                        id: abcItem

                                        width: abcGrid.cellWidth
                                        height: abcGrid.cellHeight
                                        contentHeight: abcGrid.cellHeight

                                        property alias text: label.text
                                        property bool expanded: cha === text

                                        highlightedColor: "transparent"

                                        Image {
                                            z: 0
                                            anchors.fill: parent
                                            fillMode: Image.Tile
                                            visible: !abcItem.expanded && !abcItem.pressed
                                            source: "/usr/share/harbour-chennzeihhan/images/abcbg.png"
                                        }

                                        Label {
                                            z: 1
                                            id: label
                                            anchors.centerIn: parent
                                            font.pixelSize: Theme.fontSizeExtraLarge
                                            color: !abcItem.expanded && !abcItem.pressed ? Theme.primaryColor : Theme.highlightColor
                                            opacity: 0.7
                                            text: display
                                        }

                                        onClicked: {
                                            mainView.activeRow = (mainView.cha === text) ? -1 : rowBase.rowIdx;
                                            mainView.cha = (mainView.cha === text) ? "" : text;
                                        }
                                    }
                                }
                            }

                            GridView {
                                id: grid
                                z: 1
                                clip: true
                                visible: rowBase.rowIdx === mainView.activeRow
                                height: visible ? Math.ceil(count / 3) * cellHeight : 0
                                anchors { top: abcRow.bottom; left: parent.left; right: parent.right }
                                delegate: CountriesDelegate{}
                                interactive: false
                                cellWidth: width/3; cellHeight: cellWidth * plateRatio
                                model: countriesModel
                                opacity: visible ? 1 : 0
                                Behavior on opacity { FadeAnimation{} }
                            }
                        }
                    }
                }
                Component.onCompleted:  alphabetModel.init(sortType)
            }


            Row {
                id: searchSortOptions
                anchors { left: parent.left; right: parent.right }
                visible: dbMan.dbExists && (config.databaseVersion >= config.minimumDbVersion)

                ComboBox {
                    id: sortOrdering
                    width: parent.width/2
                    label: qsTr("Sorting") + "          "

                    currentIndex: mainView.sortType

                    menu: ContextMenu {
                        MenuItem { text: qsTr("Code") }
                        MenuItem { text: qsTr("Name") }
                    }

                    onCurrentIndexChanged: mainView.sortType = currentIndex
                }

                ComboBox {
                    id: searchT
                    width: parent.width/2
                    label: qsTr("Search") + "          "

                    currentIndex: mainView.searchTarget

                    menu: ContextMenu {
                        MenuItem { text: qsTr("Code") }
                        MenuItem { text: qsTr("Name") }
                        MenuItem { text: qsTr("Both") }
                    }

                    onCurrentIndexChanged: mainView.searchTarget = currentIndex
                }
            }

            GridView {
                id: searchView
                visible: searchString !== ""
                width: parent.width
                clip: true
                anchors { left: parent.left; right: parent.right }
                height: flick.height - pageHeader.height - searchField.height
                delegate: CountriesDelegate{ search: searchString; target: searchTarget}
                cellWidth: width/3; cellHeight: cellWidth * plateRatio
                model: countriesSearch
                VerticalScrollDecorator { flickable: searchView }
            }

        }

        ViewPlaceholder {
            enabled: !dbMan.dbExists
            text: qsTr("You have no database installed. The database is not part of the application package to allow database updates without releasing new application versions. Go to the settings to download the database.")
        }

        ViewPlaceholder {
            enabled: dbMan.dbExists && (config.databaseVersion < config.minimumDbVersion)
            text: qsTr("Because of changes in the data models you have to update the database. Please go to the settings to do so. We apologize for the inconvenience.")
        }
    }
}
