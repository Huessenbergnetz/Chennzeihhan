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

    CountryPlate {
        id: plate
        width: 140; height: 90
        anchors { horizontalCenter: parent.horizontalCenter; top: parent.top; topMargin: 5 }
        color: listItem.highlighted ? highlightColor : normalColor
        text: model.sign
    }

    Label {
        id: itemTitle
        anchors { bottom: parent.bottom; bottomMargin: 5; horizontalCenter: parent.horizontalCenter }
        text: installed ? model.name : qsTr("Not installed")
        color: listItem.highlighted ? highlightColor : normalColor
        maximumLineCount: 1
        font.pixelSize: Theme.fontSizeSmall
        truncationMode: TruncationMode.Fade
        textFormat: Text.PlainText
        width: parent.width - 2* Theme.paddingMedium
        horizontalAlignment: Text.AlignHCenter
    }
}
