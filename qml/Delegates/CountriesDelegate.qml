import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Common"

ListItem {
    id: listItem

    property alias showBg: bgImage.visible
    property bool fav: config.isFav(model.sign)
    property string search
    property int target

    property string name: (target === 1 || target === 2) ? Theme.highlightText(model.name, search, Theme.highlightColor) : model.name
    property string sign: (target === 0 || target === 2) ? Theme.highlightText(model.sign, search, Theme.secondaryHighlightColor) : model.sign

    onClicked: pageStack.push(Qt.resolvedUrl("../Views/CountryView.qml"), {title: model.name, code: model.code})

    onPressAndHold: if (fav) { rmFav() } else { config.setFav(model.sign); fav = true }

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight
    contentHeight: GridView.view.cellHeight

    Image {
        id: bgImage
        z: 0
        anchors.fill: parent
        source: "/usr/share/harbour-chennzeihhan/images/country-background.png"
    }

    Image {
        id: favIcon
        z: 1
        anchors { top: parent.top; topMargin: Theme.paddingSmall; left: parent.left; leftMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-favorite"
        opacity: fav ? 1 : 0
        width: 26; height: 26
        Behavior on opacity { FadeAnimation {} }
    }

    CountryPlate {
        id: plate
        z: 1
        width: 140; height: 90
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 15 }
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        borderColor: model.colors ? model.colors : "white"
        text: sign
    }

    Image {
        id: official
        z: 1
        anchors { bottom: itemTitle.top; bottomMargin: Theme.paddingSmall; left: parent.left; leftMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-installed"
        visible: model.official
        width: 26; height: 26
    }

    Image {
        id: list
        z: 1
        anchors { bottom: itemTitle.top; bottomMargin: Theme.paddingSmall; right: parent.right; rightMargin: Theme.paddingMedium }
        source: "image://theme/icon-s-group-chat"
        visible: model.type > 0
        width: 26; height: 26
    }

    Label {
        id: itemTitle
        z: 1
        anchors { bottom: parent.bottom; bottomMargin: 5; left: parent.left; leftMargin: Theme.paddingMedium; right: parent.right; rightMargin: Theme.paddingMedium }
        text: name
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        maximumLineCount: 1
        font.pixelSize: Theme.fontSizeTiny
        truncationMode: TruncationMode.Fade
        textFormat: Text.RichText
        width: parent.width - Theme.paddingLarge
    }

    function rmFav() {
        remorse.execute(listItem, qsTr("Romving from favourites"), function() {config.removeFav(model.sign); fav = false}, 3000)
    }

    RemorseItem { id: remorse }

}
