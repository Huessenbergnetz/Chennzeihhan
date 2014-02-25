import QtQuick 2.0
import Sailfish.Silica 1.0
//import "../Models"
import "../Delegates"

Page {
    id: mainView
    objectName: "MainView"

    property string searchString

    Component.onCompleted: dataBaseExists ? countriesModel.refresh() : console.log("Database not available")
    onSearchStringChanged: countriesModel.refresh(searchString)

    SilicaGridView {
        id: listView
        anchors { left: parent.left; right: parent.right; top: parent.top; bottom: parent.bottom; bottomMargin: updateInfoPanel.open ?  updateInfoPanel.height * 1.7 : searchPanel.height * 1.5 }
        cellWidth: 180; cellHeight: 150
        currentIndex: -1

        Behavior on anchors.bottomMargin {
            NumberAnimation { duration: 300; easing.type: Easing.InOutQuad }
        }

        header: PageHeader { width: listView.width; title: "Chennzeihhan" }


        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/About.qml"))
            }
            MenuItem {
                text: qsTr("Settings")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))
            }

        }


        model: countriesModel

        delegate: CountriesDelegate { visible: dataBaseExists && (installedDbRevision >= minimumDbRevision) }

        ViewPlaceholder {
            enabled: !dataBaseExists
            text: qsTr("You have no database installed. The database is not part of the application package to allow database updates without releasing new application versions. Go to the settings to download the database.")
        }

        ViewPlaceholder {
            enabled: dataBaseExists && (installedDbRevision < minimumDbRevision)
            text: qsTr("Because of changes in the data models you have to update the database. Please go to the settings to do so. We apologize for the inconvenience.")
        }

        VerticalScrollDecorator { flickable: listView }
    }

    DockedPanel {
        id: updateInfoPanel
        width: parent.width
        height: Theme.itemSizeExtraLarge + Theme.paddingLarge

        dock: Dock.bottom
//        open: minimumDbRevision > installedDbRevision
        open: false
        visible: open

        Label {
            anchors.centerIn: parent
            text: qsTr("New content available, please update database")
            width: parent.width
            wrapMode: Text.WordWrap
            horizontalAlignment: Text.AlignHCenter

            MouseArea {
                anchors.fill: parent
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))
            }
        }

        Timer {
            interval: 5000; running: updateInfoPanel.open; repeat: false
            onTriggered: updateInfoPanel.hide()
        }
    }

    DockedPanel {
        id: searchPanel
        width: parent.width
        height: searchField.height
        open: !updateInfoPanel.open
        dock: Dock.Bottom

        SearchField {
            id: searchField
            width: parent.width
            placeholderText: qsTr("Search")
            EnterKey.onClicked: searchField.focus = false
            EnterKey.iconSource: "image://theme/icon-m-enter-close"

            Binding {
                target: mainView
                property: "searchString"
                value: searchField.text
            }
        }
    }
}
