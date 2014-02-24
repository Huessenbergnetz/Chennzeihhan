import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
import "../Delegates"

Page {
    id: mainView
    objectName: "MainView"

    SilicaGridView {
        id: listView
        anchors.fill: parent
        width: parent.width
        height: updateInfoPanel.open ? parent.height - updateInfoPanel.height : parent.height
        cellWidth: 180; cellHeight: 150

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


        model: CountriesModel {}

        delegate: CountriesDelegate {}

        ViewPlaceholder {
            enabled: !dataBaseExists
            text: qsTr("You have no database installed. The database is not part of the application package to allow database updates without releasing new application versions. Go to the settings to download the database.")
        }
    }

    DockedPanel {
        id: updateInfoPanel
        width: parent.width
        height: Theme.itemSizeExtraLarge + Theme.paddingLarge

        dock: Dock.bottom
        open: minimumDbRevision > installedDbRevision

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
}
