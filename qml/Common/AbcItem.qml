import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: root

    property string text
    property bool showBg
    width: 108; height: 108
    highlightedColor: "transparent"

    Image {
        z: 0
        anchors.fill: parent
        fillMode: Image.Tile
        visible: showBg && !root.pressed
        source: "/usr/share/harbour-chennzeihhan/images/abcbg.png"
    }

    Label {
        z: 1
        id: label
        anchors.centerIn: parent
        text: root.text
        font.pixelSize: Theme.fontSizeExtraLarge
        color: showBg && !root.pressed ? Theme.primaryColor : Theme.highlightColor
        opacity: 0.7
    }
}
