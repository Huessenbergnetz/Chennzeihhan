import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
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

//    Component.onCompleted: dataBaseExists ? countriesModel.refresh(searchString, searchTarget, sortType) : console.log("Database not available")

    onSearchStringChanged: countriesModel.refresh(searchString, searchTarget, sortType)
//    onSortTypeChanged: countriesModel.refresh(searchString, searchTarget, sortType)
    onSortTypeChanged: if (cha !== "") countriesModel.setFirstChar(cha, sortType)
    onSearchTargetChanged: countriesModel.refresh(searchString, searchTarget, sortType)

    function toggleList(c, row)
    {
        if (cha === c) {
            closeList(row)
            cha = ""
            activeRow = 0
        } else if (cha !== c && activeRow === row) {
            repopulateList(row, c)
            cha = c
        } else if (cha !== c && activeRow !== row) {
            closeList(activeRow)
            openList(row, c)
            cha = c
            activeRow = row
        }
    }

    function closeList(nr) {
        switch(nr){
        case 1:
            gv1.visible = false
            break;
        case 2:
            gv2.visible = false
            break;
        case 3:
            gv3.visible = false
            break;
        case 4:
            gv4.visible = false
            break;
        case 5:
            gv5.visible = false
            break;
        case 6:
            gv6.visible = false
            break;
        default:
            break;
        }
    }

    function repopulateList(nr, text) {
        switch(nr){
        case 1:
            gv1.opacity = 0
            gv1.model.setFirstChar(text, sortType)
            gv1.timer.restart()
            break;
        case 2:
            gv2.opacity = 0
            gv2.model.setFirstChar(text, sortType)
            gv2.timer.restart()
            break;
        case 3:
            gv3.opacity = 0
            gv3.model.setFirstChar(text, sortType)
            gv3.timer.restart()
            break;
        case 4:
            gv4.opacity = 0
            gv4.model.setFirstChar(text, sortType)
            gv4.timer.restart()
            break;
        case 5:
            gv5.opacity = 0
            gv5.model.setFirstChar(text, sortType)
            gv5.timer.restart()
            break;
        case 6:
            gv6.opacity = 0
            gv6.model.setFirstChar(text, sortType)
            gv6.timer.restart()
            break;
        default:
            break;
        }
    }

    function openList(nr, text) {
        switch(nr){
        case 1:
            gv1.model.setFirstChar(text, sortType)
            gv1.visible = true
            break;
        case 2:
            gv2.model.setFirstChar(text, sortType)
            gv2.visible = true
            break;
        case 3:
            gv3.model.setFirstChar(text, sortType)
            gv3.visible = true
            break;
        case 4:
            gv4.model.setFirstChar(text, sortType)
            gv4.visible = true
            break;
        case 5:
            gv5.model.setFirstChar(text, sortType)
            gv5.visible = true
            break;
        case 6:
            gv6.model.setFirstChar(text, sortType)
            gv6.visible = true
            break;
        default:
            break;
        }
    }

    SilicaFlickable {
        PageHeader { title: "Chennzeihhan" }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: favourites.height + chooser.height + sortOrdering.height + 6 * Theme.paddingLarge

        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/About.qml"))
            }
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))
            }
            MenuItem {
                text: qsTr("Help/Legend")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Help.qml"))
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

            visible: count > 0
            height: visible ? calcHeight(count / 3) * cellHeight : 0
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge }
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
            id: chooser
            anchors { top: favourites.visible ? favourites.bottom : parent.top; left: parent.left; right: parent.right; topMargin: favourites.visible ? Theme.paddingLarge : 4 * Theme.paddingLarge }
            height: row1.height + gv1.height + row2.height + gv2.height + row3.height + gv3.height + row4.height + gv4.height + row5.height + gv5.height + row6.height + gv6.height
            visible: dataBaseExists && (installedDbRevision >= minimumDbRevision)

            Row {
                id: row1
                height: 108
                anchors { top: parent.top; left: parent.left; right: parent.right }
                AbcItem { text: "A"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "B"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "C"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "D"; showBg: cha !== text; onClicked: toggleList(text, 1) }
                AbcItem { text: "E"; showBg: cha !== text; onClicked: toggleList(text, 1) }
            }

            AbcGrid {
                id: gv1
                anchors { left: parent.left; right: parent.right; top: row1.bottom }
            }

            Row {
                id: row2
                height: 108
                anchors { top: gv1.bottom; left: parent.left; right: parent.right }
                AbcItem { text: "F"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "G"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "H"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "I"; showBg: cha !== text; onClicked: toggleList(text, 2) }
                AbcItem { text: "J"; showBg: cha !== text; onClicked: toggleList(text, 2) }
            }

            AbcGrid {
                id: gv2
                anchors { left: parent.left; right: parent.right; top: row2.bottom }
            }

            Row {
                id: row3
                height: 108
                anchors { top: gv2.bottom; left: parent.left; right: parent.right }
                AbcItem { text: "K"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "L"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "M"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "N"; showBg: cha !== text; onClicked: toggleList(text, 3) }
                AbcItem { text: "O"; showBg: cha !== text; onClicked: toggleList(text, 3) }
            }

            AbcGrid {
                id: gv3
                anchors { left: parent.left; right: parent.right; top: row3.bottom }
            }

            Row {
                id: row4
                height: 108
                anchors { top: gv3.bottom; left: parent.left; right: parent.right }
                AbcItem { text: "P"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "Q"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "R"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "S"; showBg: cha !== text; onClicked: toggleList(text, 4) }
                AbcItem { text: "T"; showBg: cha !== text; onClicked: toggleList(text, 4) }
            }

            AbcGrid {
                id: gv4
                anchors { left: parent.left; right: parent.right; top: row4.bottom }
            }

            Row {
                id: row5
                height: 108
                anchors { top: gv4.bottom; left: parent.left; right: parent.right }
                AbcItem { text: "U"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "V"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "W"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "X"; showBg: cha !== text; onClicked: toggleList(text, 5) }
                AbcItem { text: "Y"; showBg: cha !== text; onClicked: toggleList(text, 5) }
            }

            AbcGrid {
                id: gv5
                anchors { left: parent.left; right: parent.right; top: row5.bottom }
            }

            Row {
                id: row6
                height: 108
                anchors { top: gv5.bottom; left: parent.left; right: parent.right }
                AbcItem { text: "Z"; showBg: cha !== text; onClicked: toggleList(text, 6) }
            }

            AbcGrid {
                id: gv6
                anchors { left: parent.left; right: parent.right; top: row6.bottom }
            }

        }

        ComboBox {
            id: sortOrdering
            anchors { top: chooser.bottom; topMargin: 20 }
            width: parent.width
            label: qsTr("Sorting")

            currentIndex: mainView.sortType

            menu: ContextMenu {
                MenuItem { text: qsTr("Registration codes") }
                MenuItem { text: qsTr("Country name") }
            }

            onCurrentIndexChanged: mainView.sortType = currentIndex
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


//    SilicaGridView {
//        id: listView
//        anchors { left: parent.left; right: parent.right; top: parent.top; bottom: parent.bottom; bottomMargin: searchPanel.height * 1.5 }
//        cellWidth: 180; cellHeight: 150
//        currentIndex: -1

//        Behavior on anchors.bottomMargin {
//            FadeAnimation {}
//        }

//        header: PageHeader { width: listView.width; title: "Chennzeihhan"; }

//        PullDownMenu {
//            MenuItem {
//                text: qsTr("About")
//                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/About.qml"))
//            }
//            MenuItem {
//                text: qsTr("Settings")
//                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))
//            }

//        }


//        model: countriesModel

//        delegate: CountriesDelegate { visible: dataBaseExists && (installedDbRevision >= minimumDbRevision) }

//        ViewPlaceholder {
//            enabled: !dataBaseExists
//            text: qsTr("You have no database installed. The database is not part of the application package to allow database updates without releasing new application versions. Go to the settings to download the database.")
//        }

//        ViewPlaceholder {
//            enabled: dataBaseExists && (installedDbRevision < minimumDbRevision)
//            text: qsTr("Because of changes in the data models you have to update the database. Please go to the settings to do so. We apologize for the inconvenience.")
//        }

//        VerticalScrollDecorator { flickable: listView }
//    }





//    DockedPanel {
//        id: updateInfoPanel
//        width: parent.width
//        height: Theme.itemSizeExtraLarge + Theme.paddingLarge

//        dock: Dock.bottom
////        open: minimumDbRevision > installedDbRevision
//        open: false
//        visible: open

//        Label {
//            anchors.centerIn: parent
//            text: qsTr("New content available, please update database")
//            width: parent.width
//            wrapMode: Text.WordWrap
//            horizontalAlignment: Text.AlignHCenter

//            MouseArea {
//                anchors.fill: parent
//                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))
//            }
//        }

//        Timer {
//            interval: 5000; running: updateInfoPanel.open; repeat: false
//            onTriggered: updateInfoPanel.hide()
//        }
//    }

//    DockedPanel {
//        id: searchPanel
//        width: parent.width
//        height: searchField.height
//        open: true
//        dock: Dock.Bottom

//        SearchField {
//            id: searchField
//            width: parent.width
//            placeholderText: qsTr("Search")
//            EnterKey.onClicked: searchField.focus = false
//            EnterKey.iconSource: "image://theme/icon-m-enter-close"

//            Binding {
//                target: mainView
//                property: "searchString"
//                value: searchField.text
//            }
//        }
//    }
}
