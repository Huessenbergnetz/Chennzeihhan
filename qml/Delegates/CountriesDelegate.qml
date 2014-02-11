import QtQuick 2.0
import Sailfish.Silica 1.0

BackgroundItem {
    id: listItem

    onClicked: pageStack.push(Qt.resolvedUrl("../Views/CountryView.qml"), {title: model.name, code: model.code})

    width: GridView.view.cellWidth
    height: GridView.view.cellHeight

    Image {
        id: coa
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 5 }
        source: "/usr/share/harbour-chennzeihhan/images/countries/" + model.code + ".png"
        sourceSize.width: 150
        width: 150
    }

    Label {
        id: itemTitle
        anchors { bottom: parent.bottom; bottomMargin: 5 }
        text: model.name
        color: listItem.highlighted ? Theme.highlightColor : Theme.primaryColor
        maximumLineCount: 1
        truncationMode: TruncationMode.Fade
        textFormat: Text.PlainText
        width: parent.width
        horizontalAlignment: Text.AlignHCenter
    }
}
