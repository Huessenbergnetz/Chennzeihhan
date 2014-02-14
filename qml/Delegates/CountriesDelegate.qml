import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Common"

BackgroundItem {
    id: listItem

    onClicked: pageStack.push(Qt.resolvedUrl("../Views/CountryView.qml"), {title: model.name, code: model.code})

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    CountryPlate {
        id: plate
        width: 140; height: 90
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 5 }
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        text: model.sign
    }

    Label {
        id: itemTitle
        anchors { bottom: parent.bottom; bottomMargin: 5; horizontalCenter: parent.horizontalCenter }
        text: model.name
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        maximumLineCount: 1
        font.pixelSize: Theme.fontSizeSmall
        truncationMode: TruncationMode.Fade
        textFormat: Text.PlainText
        width: parent.width - 2* Theme.paddingMedium
        horizontalAlignment: Text.AlignHCenter
    }
}
