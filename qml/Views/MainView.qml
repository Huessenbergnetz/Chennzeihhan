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
        activeRow = (cha === c) ? 0 : row;
        cha = (cha === c) ? "" : c;
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

            AbcRow {
                id: row1
                cha: mainView.cha
                onClicked: toggleList(txt, 1)
                cont: ["A", "B", "C", "D", "E"]
            }

            AbcGrid {
                id: gv1
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 1 && showMainContent
            }

            AbcRow {
                id: row2
                cha: mainView.cha
                onClicked: toggleList(txt, 2)
                cont: ["F", "G", "H", "I", "J"]
            }

            AbcGrid {
                id: gv2
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 2 && showMainContent
            }

            AbcRow {
                id: row3
                cha: mainView.cha
                onClicked: toggleList(txt, 3)
                cont: ["K", "L", "M", "N", "O"]
            }

            AbcGrid {
                id: gv3
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 3 && showMainContent
            }

            AbcRow {
                id: row4
                cha: mainView.cha
                onClicked: toggleList(txt, 4)
                cont: ["P", "Q", "R", "S", "T"]
            }

            AbcGrid {
                id: gv4
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 4 && showMainContent
            }


            AbcRow {
                id: row5
                cha: mainView.cha
                onClicked: toggleList(txt, 5)
                cont: ["U", "V", "W", "X", "Y"]
            }

            AbcGrid {
                id: gv5
                anchors { left: parent.left; right: parent.right }
                visible: activeRow === 5 && showMainContent
            }


            AbcRow {
                id: row6
                cha: mainView.cha
                onClicked: toggleList(txt, 6)
                cont: ["Z"]
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
