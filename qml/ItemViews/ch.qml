import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: itemView
    objectName: "ItemView"

    property int itemId

    property string countryCode: "ch"

    property string sign
    property string name
    property string capital
    property string wikipedia

    function getItemData()
    {
        var itemData = itemModel.getItemData(countryCode, itemId);
        sign = itemData["sign"];
        name = itemData["name"];
        capitalText.text = itemData["capital"];
        wikipedia = itemData["wikipedia"];
    }

    Component.onCompleted: {
        getItemData()
        coverConnector.country = qsTr("Switzerland")
        coverConnector.state = ""
        coverConnector.name = name
        coverConnector.sign = sign
    }

    onStatusChanged: {
        if (status == PageStatus.Active && wikipedia !== "") {
            pageStack.pushAttached(Qt.resolvedUrl("../Views/ItemWebView.qml"), {itemUrl: "http://de.m.wikipedia.org/wiki/" + wikipedia})
        }
    }

    SilicaFlickable {
        id: singleItem
        PageHeader { title: sign }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: contentCol.height + Theme.paddingLarge


        Column {
            id: contentCol
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge; leftMargin: Theme.paddingLarge }


            Label {
                id: nameLabel
                text: qsTr("Canton %2").arg(name)
                textFormat: Text.PlainText
                color: Theme.highlightColor
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            ItemEntry {
                id: capitalText
                header: qsTr("Capital")
                icon: "image://theme/icon-s-task"
            }
        }
    }
}
