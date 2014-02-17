import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
import "../Delegates"

Page {
    id: mainView
    objectName: "MainView"

    property bool dataBaseExists: dbMan.checkDB()

    Connections {
        target: dlMan
        onDbDownloadFinished: checkDbTimer.start()
    }

    Timer {
        id: checkDbTimer; interval: 200; running: false; repeat: false
        onTriggered: dataBaseExists = dbMan.checkDB()
    }

    SilicaGridView {
        id: listView
        anchors.fill: parent
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

        delegate: CountriesDelegate { visible: dataBaseExists}

        ViewPlaceholder {
            enabled: !dataBaseExists
            text: qsTr("You have no database installed. The database is not part of the application package to allow database updates without releasing new application versions for every modification. Go to the settings to download the database.")
        }
    }
}
