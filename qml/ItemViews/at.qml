import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: atItemView
    objectName: "ItemView"

    property int itemId

    property string countryCode: "at"

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
        capitalText.contentText = itemData["capital"];
        type = itemData["type"];
        stateLabel.text = itemData["state"];
        founded = itemData["founded"];
        disbanded = itemData["disbanded"];
        optionalText.contentText = itemData["optional"];
        succId = itemData["succId"];
        succName = itemData["succName"];
        succType = itemData["succType"];
        succSign = itemData["succSign"];
        tpoId = itemData["tpoId"];
        tpoName = itemData["tpoName"];
        tpoType = itemData["tpoType"];
        tpoSign = itemData["tpoSign"];
        optSignsText.contentText = itemData["optionalSigns"];
        wikipedia = itemData["wikipedia"];

        antecessorModel.refresh(countryCode, itemId)
    }

    Component.onCompleted: {
        getItemData()
    }

    onStatusChanged: {
        coverConnector.country = qsTr("Austria")
        coverConnector.name = atItemView.name
        coverConnector.sign = atItemView.sign
        coverConnector.type = atItemView.type
        coverConnector.state = stateLabel.text
        if (status == PageStatus.Active && wikipedia !== "") {
            pageStack.pushAttached(Qt.resolvedUrl("ItemWebView.qml"), {wpLang: "de", wpName: wikipedia})
        }
    }

    SilicaFlickable {
        id: singleItem
        PageHeader { title: sign }
        anchors.fill: parent
        VerticalScrollDecorator {}
        contentHeight: headerCol.height + contentCol.height + listCol.height + Theme.paddingLarge


        Column {
            id: headerCol
            anchors { top: parent.top; left: parent.left; right: parent.right; topMargin: 4 * Theme.paddingLarge; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge }

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
        }


        Column {
            id: contentCol
            anchors { top: headerCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge }
            spacing:Theme.paddingLarge

            ItemEntry {
                id: capitalText
                header: qsTr("Capital")
                icon: "image://theme/icon-s-task"
            }

            ItemEntry {
                id: existenceText
                header: disbanded === 0 ? qsTr("Assigend since") : qsTr("Assigned from")
                contentText: disbanded === 0 ? founded : founded + " - " + disbanded
                icon: "image://theme/icon-s-date"
            }

            ItemEntry {
                id: optSignsText
                header: qsTr("Optional plate signs")
                visible: contentText !== ""
                icon: "image://theme/icon-l-share"
            }

            ItemEntry {
                id: optionalText
                header: qsTr("Sign optional available since")
                visible: contentText !== "0"
                icon: "image://theme/icon-m-refresh"
            }
        }

        Column {
            id: listCol
            anchors { top: contentCol.bottom; left: parent.left; right: parent.right; topMargin: Theme.paddingLarge; leftMargin: Theme.paddingLarge; rightMargin: Theme.paddingLarge }

            ItemEntry {
                id: mergedText
                header: qsTr("Merged into")
                visible: succId !== 0
                icon: "image://theme/icon-s-device-upload"
                contentText: qsTr("%1 - %2 %3").arg(succSign).arg(succType).arg(succName)
                clickable: true
                onClicked: pageStack.replace(Qt.resolvedUrl("at.qml"), {itemId: succId}, PageStackAction.Immediate)
            }

            ItemEntry {
                id: todayPartOfText
                header: qsTr("Today part of")
                visible: tpoId !== 0
                icon: "image://theme/icon-m-location"
                contentText: qsTr("%1 - %2 %3").arg(tpoSign).arg(tpoType).arg(tpoName)
                clickable: true
                onClicked: pageStack.replace(Qt.resolvedUrl("at.qml"), {itemId: tpoId}, PageStackAction.Immediate)
            }

            ItemEntry {
                id: antecessors
                header: qsTr("Includes this old plate signs")
                visible: count > 0
                icon: "image://theme/icon-m-levels"
                repeaterModel: antecessorModel
                list: true
                onModelClicked: pageStack.replace(Qt.resolvedUrl("at.qml"), {itemId: modelId}, PageStackAction.Immediate)
            }
        }
    }
}
