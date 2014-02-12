import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: itemView
    objectName: "ItemView"

    property int itemId

    property string countryCode: "de"

    property string sign
    property string name
    property string capitol
    property string type
    property string state
    property string assign
    property int successor
    property string admin
    property int closed
    property int optional
    property bool valid
    property int succId
    property string succName
    property string succType
    property string succSign
    property string optSigns
    property string wikipedia

    function getItemData()
    {
//        var itemData = deItemModel.getItemData(itemId);
        var itemData = itemModel.getItemData(countryCode, itemId);
        sign = itemData["sign"];
        name = itemData["name"];
        capitalText.text = itemData["capitol"];
        type = itemData["type"];
        stateLabel.text = itemData["state"];
        allocatedText.text = itemData["assign"];
        successor = itemData["successor"];
//        managedByText.text = itemData["admin"];
        closedText.text = itemData["closed"];
        optionalText.text = itemData["optional"];
        valid = itemData["valid"];
        succId = itemData["succId"];
        succName = itemData["succName"];
        succType = itemData["succType"];
        succSign = itemData["succSign"];
        optSignsText.text = itemData["optionalSigns"];
        wikipedia = itemData["wikipedia"];

        deAntecessorModel.refresh(itemId)
    }

    Component.onCompleted: {
        getItemData()
        coverConnector.country = qsTr("Germany")
        coverConnector.name = name
        coverConnector.sign = sign
        coverConnector.state = stateLabel.text
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
                text: qsTr("%1 %2").arg(type).arg(name)
                textFormat: Text.PlainText
                color: Theme.highlightColor
                width: parent.width
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }

            Label {
                id: stateLabel
                textFormat: Text.PlainText
                color: Theme.highlightColor
            }

            SectionHeader { text: qsTr("Capital") }

            Text {
                id: capitalText
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
            }

            SectionHeader { text: valid ? qsTr("Existing since") : qsTr("Existed from") }

            Text {
                id: allocatedText
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
            }

            SectionHeader { text: qsTr("Optional plate signs"); visible: optSignsText.text !== ""}

            Text {
                id: optSignsText
                visible: text !== ""
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
            }

            SectionHeader { text: qsTr("Disbanded"); visible: closedText.visible }

            Text {
                id: closedText
                visible: text !== "0"
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
            }

            SectionHeader { text: qsTr("Sign optional available since"); visible: optionalText.visible }

            Text {
                id: optionalText
                visible: text !== "0"
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.primaryColor
            }

            SectionHeader { text: qsTr("Merged into"); visible: succId !== 0 }

            BackgroundItem {
                id: bgItem
                width: parent.width + Theme.paddingLarge
                height: Theme.itemSizeSmall
                anchors.left: parent.left
                anchors.leftMargin: -Theme.paddingLarge
                visible: succId !== 0
                Label {
                    id: mergedText
                    text: qsTr("%1 - %2 %3").arg(succSign).arg(succType).arg(succName)
                    width: parent.width
                    font.pixelSize: Theme.fontSizeSmall
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    color: bgItem.highlighted ? Theme.highlightColor : Theme.primaryColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.rightMargin: Theme.paddingLarge
                }
                onClicked: pageStack.replace(Qt.resolvedUrl("de.qml"), {itemId: succId}, PageStackAction.Immediate)
            }

//            SectionHeader { text: qsTr("Managed by"); visible: managedByText.text !== "" }

//            BackgroundItem {
//                id: bgItem2
//                width: parent.width + Theme.paddingLarge
//                height: Theme.itemSizeSmall
//                anchors.left: parent.left
//                anchors.leftMargin: -Theme.paddingLarge
//                visible: managedByText.text !== ""
//                Label {
//                    id: managedByText
//                    visible: text !== ""
//                    width: parent.width
//                    maximumLineCount: 1
//                    truncationMode: TruncationMode.Fade
//                    font.pixelSize: Theme.fontSizeSmall
//                    color: bgItem2.highlighted ? Theme.highlightColor : Theme.primaryColor
//                    anchors.verticalCenter: parent.verticalCenter
//                    anchors.left: parent.left
//                    anchors.right: parent.right
//                    anchors.leftMargin: Theme.paddingLarge
//                    anchors.rightMargin: Theme.paddingLarge
//                }
//            }

            SectionHeader { text: qsTr("Includes this old districts"); visible: succRep.visible }

            Repeater {
                id: succRep
                visible: count > 0
                model: deAntecessorModel
                delegate: BackgroundItem {
                    id: bgItem3
                    width: contentCol.width + Theme.paddingLarge
                    height: Theme.itemSizeSmall
                    anchors.left: contentCol.left
                    anchors.leftMargin: -Theme.paddingLarge
                    visible: succRep.visible
                    Label {
                        id: succOfText
                        width: parent.width
                        maximumLineCount: 1
                        truncationMode: TruncationMode.Fade
                        text: qsTr("%1 - %2 %3").arg(model.sign).arg(model.type).arg(model.name)
                        font.pixelSize: Theme.fontSizeSmall
                        color: bgItem3.highlighted ? Theme.highlightColor : Theme.primaryColor
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.left: parent.left
                        anchors.right: parent.right
                        anchors.leftMargin: Theme.paddingLarge
                        anchors.rightMargin: Theme.paddingLarge
                    }
                    onClicked: pageStack.replace(Qt.resolvedUrl("de.qml"), {itemId: model.itemId}, PageStackAction.Immediate)
                }
            }
        }
    }
}
