import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Delegates"
import "../Common"

Page {
    id: mainView
    objectName: "MainView"

    property string searchString
    property int searchTarget: 0
    property int sortType: 0
    property string cha: ""
    property int activeRow: 0
    property bool updated: true
    property bool showMainContent: dataBaseExists && (installedDbRevision >= minimumDbRevision) && searchString === ""

    Component.onCompleted: {
        searchTarget = config.get("display/search", 0)
        sortType = config.get("display/ordering", 0)
    }

    Connections {
        target: config
        onConfigChanged: {
            searchTarget = config.get("display/search", 0)
            searchT.currentIndex = config.get("display/search", 0)
            sortType = config.get("display/ordering", 0)
            sortOrdering.currentIndex = config.get("display/ordering", 0)
        }
    }

    onSearchStringChanged: countriesSearch.refresh(searchString, searchTarget, sortType)
    onSortTypeChanged: if (cha !== "") { countriesModel.setFirstChar(cha, sortType) } else if (searchString !== "") { countriesSearch.refresh(searchString, searchTarget, sortType) }
    onSearchTargetChanged: if (searchString !== "") countriesSearch.refresh(searchString, searchTarget, sortType)
    onChaChanged: countriesModel.setFirstChar(cha, sortType)

    function toggleList(c, row)
    {
        if (cha === c) {
            activeRow = 0
            cha = ""
        } else {
            activeRow = row
            cha = c
        }
    }

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
                visible: dataBaseExists && (installedDbRevision >= minimumDbRevision)
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

                function calcHeight(h) {
                    var h1 = h;
                    var h2 = Math.round(h)
                    var h3
                    if (h2 < h1) {
                        h3 = h2 +1
                    } else {
                        h3 = h2;
                    }
                    return h3
                }

                visible: count > 0 && showMainContent
                height: visible ? calcHeight(count / 3) * cellHeight : 0
                anchors { left: parent.left; right: parent.right }
                delegate: CountriesDelegate{ showBg: false}
                interactive: false
                cellWidth: 180; cellHeight: 150
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


            Row {
                id: row1
                height: 108
                anchors { left: parent.left; right: parent.right }
                visible: showMainContent
                AbcItem { text: "A"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "B"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "C"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "D"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "E"; showBg: cha !== text; onClicked: toggleList(text, 1) }
            }

            AbcGrid {
                id: gv1
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 1 && showMainContent
            }

            Row {
                id: row2
                height: 108
                anchors { left: parent.left; right: parent.right }
                visible: showMainContent
                AbcItem { text: "F"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "G"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "H"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "I"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "J"; showBg: cha !== text; onClicked: toggleList(text, 2) }
            }

            AbcGrid {
                id: gv2
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 2 && showMainContent
            }

            Row {
                id: row3
                height: 108
                anchors { left: parent.left; right: parent.right }
                visible: showMainContent
                AbcItem { text: "K"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "L"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "M"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "N"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "O"; showBg: cha !== text; onClicked: toggleList(text, 3) }
            }

            AbcGrid {
                id: gv3
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 3 && showMainContent
            }

            Row {
                id: row4
                height: 108
                anchors { left: parent.left; right: parent.right }
                visible: showMainContent
                AbcItem { text: "P"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "Q"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "R"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "S"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "T"; showBg: cha !== text; onClicked: toggleList(text, 4) }
            }

            AbcGrid {
                id: gv4
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 4 && showMainContent
            }

            Row {
                id: row5
                height: 108
                anchors { left: parent.left; right: parent.right }
                visible: showMainContent
                AbcItem { text: "U"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "V"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "W"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "X"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "Y"; showBg: cha !== text; onClicked: toggleList(text, 5) }
            }

            AbcGrid {
                id: gv5
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 5 && showMainContent
            }

            Row {
                id: row6
                height: 108
                anchors { left: parent.left; right: parent.right }
                visible: showMainContent
                AbcItem { text: "Z"; showBg: cha !== text; onClicked: toggleList(text, 6) }
            }

            AbcGrid {
                id: gv6
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 6 && showMainContent
            }

            Row {
                id: searchSortOptions
                anchors { left: parent.left; right: parent.right }

                ComboBox {
                    id: sortOrdering
                    width: parent.width/2
                    label: qsTr("Sorting")

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
                    label: qsTr("Search")

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

                function calcHeight(h) {
                    var h1 = h;
                    var h2 = Math.round(h)
                    var h3
                    if (h2 < h1) {
                        h3 = h2 +1
                    } else {
                        h3 = h2;
                    }
                    return h3
                }

                visible: searchString !== ""
                width: parent.width
                clip: true
                anchors { left: parent.left; right: parent.right }
                height: flick.height - pageHeader.height - searchField.height
                delegate: CountriesDelegate{ search: searchString; target: searchTarget}
                cellWidth: 180; cellHeight: 150
                model: countriesSearch
                VerticalScrollDecorator { flickable: searchView }
            }

        }

        ViewPlaceholder {
            enabled: !dataBaseExists
            text: qsTr("You have no database installed. The database is not part of the application package to allow database updates without releasing new application versions. Go to the settings to download the database.")
        }

        ViewPlaceholder {
            enabled: dataBaseExists && (installedDbRevision < minimumDbRevision)
            text: qsTr("Because of changes in the data models you have to update the database. Please go to the settings to do so. We apologize for the inconvenience.")
        }
    }
}
