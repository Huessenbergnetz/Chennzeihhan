import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Common"

BackgroundItem {
    id: listItem

    property bool installed: model.dbRevision <= installedDbRevision
    property string highlightColor: installed ? Theme.highlightColor : "#B0B0B0"
    property string normalColor: installed ? Theme.primaryColor : "#B0B0B0"

    onClicked: installed ? pageStack.push(Qt.resolvedUrl("../Views/CountryView.qml"), {title: model.name, code: model.code}) : pageStack.push(Qt.resolvedUrl("../Pages/Settings.qml"))

    visible: dataBaseExists

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    Image {
        anchors.fill: parent
        source: "/usr/share/harbour-chennzeihhan/images/country-background.png"
    }

    Image {
        id: official
        z: 1
        anchors { top: parent.top; topMargin: Theme.paddingMedium; left: parent.left; leftMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-installed"
        visible: model.official
        width: 26; height: 26
    }

    CountryPlate {
        id: plate
        z: 1
        width: 140; height: 90
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 25 }
        color: listItem.highlighted ? highlightColor : normalColor
        text: model.sign
    }

    Label {
        id: itemTitle
        z: 1
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
        text: installed ? model.name : qsTr("Not installed")
        color: listItem.highlighted ? highlightColor : normalColor
        maximumLineCount: 1
        font.pixelSize: Theme.fontSizeTiny
        truncationMode: TruncationMode.Fade
        textFormat: Text.PlainText
        width: parent.width - Theme.paddingLarge
//        horizontalAlignment: Text.AlignHCenter
    }
}
