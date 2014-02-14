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
    property int founded
    property int disbanded
    property int optional
    property int succId  // data for the successor
    property string succName
    property string succType
    property string succSign
    property int tpoId // data for the district it is part of today if it is not the same as successor
    property string tpoName
    property string tpoType
    property string tpoSign
    property string optSigns
    property string wikipedia

    function getItemData()
    {
        var itemData = itemModel.getItemData(countryCode, itemId);
        sign = itemData["sign"];
        name = itemData["name"];
        capitalText.text = itemData["capital"];
        type = itemData["type"];
        stateLabel.text = itemData["state"];
        founded = itemData["founded"];
        disbanded = itemData["disbanded"];
        optionalText.text = itemData["optional"];
        succId = itemData["succId"];
        succName = itemData["succName"];
        succType = itemData["succType"];
        succSign = itemData["succSign"];
        tpoId = itemData["tpoId"];
        tpoName = itemData["tpoName"];
        tpoType = itemData["tpoType"];
        tpoSign = itemData["tpoSign"];
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

            SectionHeader { text: disbanded === 0 ? qsTr("Existing since") : qsTr("Existed from") }

            Text {
                id: existenceText
                text: disbanded === 0 ? founded : founded + " - " + disbanded
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

            SectionHeader { text: qsTr("Today part of"); visible: tpoId !== 0 }

            BackgroundItem {
                id: bgItem2
                width: parent.width + Theme.paddingLarge
                height: Theme.itemSizeSmall
                anchors.left: parent.left
                anchors.leftMargin: -Theme.paddingLarge
                visible: tpoId !== 0
                Label {
                    id: todayPartOfText
                    text: qsTr("%1 - %2 %3").arg(tpoSign).arg(tpoType).arg(tpoName)
                    width: parent.width
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    font.pixelSize: Theme.fontSizeSmall
                    color: bgItem2.highlighted ? Theme.highlightColor : Theme.primaryColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.rightMargin: Theme.paddingLarge
                }
                onClicked: pageStack.replace(Qt.resolvedUrl("de.qml"), {itemId: tpoId}, PageStackAction.Immediate)
            }

            SectionHeader { text: disbanded === 0 ? qsTr("Includes this old districts") : qsTr("Included this old districts"); visible: succRep.visible }

            Repeater {
                id: succRep
                visible: count > 0
                height: count * Theme.itemSizeSmall
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
