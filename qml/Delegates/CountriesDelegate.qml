import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Common"

BackgroundItem {
    id: listItem

    onClicked: pageStack.push(Qt.resolvedUrl("../Views/CountryView.qml"), {title: model.name, code: model.code})

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    Image {
        z: 0
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

    Image {
        id: list
        z: 1
        anchors { top: parent.top; topMargin: Theme.paddingMedium; right: parent.right; rightMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-group-chat"
        visible: model.type > 0
        width: 26; height: 26
    }

    CountryPlate {
        id: plate
        z: 1
        width: 140; height: 90
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 25 }
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        borderColor: model.colors ? model.colors : "white"
        text: model.sign
    }

    Label {
        id: itemTitle
        z: 1
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; leftMargin: Theme.paddingMedium; right: parent.right; rightMargin: Theme.paddingMedium }
        text: model.name
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        maximumLineCount: 1
        font.pixelSize: Theme.fontSizeTiny
        truncationMode: TruncationMode.Fade
        textFormat: Text.PlainText
        width: parent.width - Theme.paddingLarge
    }
}
