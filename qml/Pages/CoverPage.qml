import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Common"


CoverBackground {

    CoverPlaceholder {
        visible: coverConnector.mode === "overview"
        text: "Chenn zeihhan"
        icon.source: "/usr/share/icons/hicolor/86x86/apps/harbour-chennzeihhan.png"
    }

    Column {
        id: itemInfo
        visible: coverConnector.mode === "item"
        y: Theme.paddingLarge
        anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
        spacing: 3
        Image {
            source: "/usr/share/icons/hicolor/86x86/apps/harbour-chennzeihhan.png"
            width: 86
            height: 86
            anchors.horizontalCenter: parent.horizontalCenter
            opacity: 0.4
        }
        Label {
            id: sign
            text: coverConnector.sign
            font.pixelSize: Theme.fontSizeHuge
            anchors.horizontalCenter: parent.horizontalCenter
        }
        Label {
            id: name
            text: coverConnector.name
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
        }
        Label {
            id: state
            text: coverConnector.state
            visible: text !== ""
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
        }
        Label {
            id: country
            text: coverConnector.country
            width: parent.width
            color: Theme.secondaryColor
            maximumLineCount: 1
            truncationMode: TruncationMode.Fade
            font.pixelSize: Theme.fontSizeSmall
        }
    }

    Item {
        id: countryInfo
        visible: coverConnector.mode === "country"
        anchors.fill: parent
        CountryPlate {
            y: Theme.paddingLarge
            width: 140; height: 90
            anchors.horizontalCenter: parent.horizontalCenter
            color: "white"
            borderColor: coverConnector.colors
            text: coverConnector.sign
            onBorderColorChanged: drawEllipse()
        }
        Label {
            text: coverConnector.name
            width: parent.width - 2* Theme.paddingLarge
            color: Theme.secondaryColor
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            anchors.centerIn: parent
            horizontalAlignment: Text.AlignHCenter
        }
    }
}


