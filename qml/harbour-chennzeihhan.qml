import QtQuick 2.0
import Sailfish.Silica 1.0
import "Views"

ApplicationWindow
{
    id: chennzeihhan

    property bool dataBaseExists: dbMan.checkDB()
    property int installedDbRevision: dlMan.getLocalDBVersion()
    property int minimumDbRevision: 8


    function getCoverMode() {
        switch(pageStack.currentPage.objectName) {
        case "ItemView":
            return "item";
        case "CountryView":
            return "country"
        case "WikiView":
            return "wikipedia"
        default:
            return "overview"
        }
    }

    Connections {
        target: dlMan
        onDbDownloadFinished: { checkDbTimer.start(); installedDbRevision = dlMan.getLocalDBVersion() }
    }

    Timer {
        id: checkDbTimer; interval: 200; running: false; repeat: false
        onTriggered: { dataBaseExists = dbMan.checkDB(); countriesModel.refresh() }
    }

    initialPage: Component { MainView { } }
    cover: Qt.resolvedUrl("Pages/CoverPage.qml")

    QtObject {
        id: coverConnector

        property string country
        property string name
        property string type
        property string sign
        property string state
        property string colors
        property string countryName
        property string countrySign
        property string countryColors
        property string mode: "overview"
    }


    Connections {
        target: pageStack
        onCurrentPageChanged: coverConnector.mode = getCoverMode()
    }
}


