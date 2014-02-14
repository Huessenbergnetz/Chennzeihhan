import QtQuick 2.0
import Sailfish.Silica 1.0

Item {
    id: root

    property alias header: header.text
    property alias icon: icon.source
    property alias repeaterModel: rep.model
    property alias count: rep.count
    property string contentText
    property bool clickable: false
    property bool list: false

    signal clicked()
    signal modelClicked(int modelId)

    anchors { right: parent.right; left: parent.left }
    height: col.height
    width: (parent ? parent.width : Screen.width)

    Column {
        id: col
        width: parent.width

        Row {
            id: headerRow
            width: parent.width

            Image {
                id: icon
                width: Theme.fontSizeSmall; height: Theme.fontSizeSmall;
                smooth: true
                anchors.verticalCenter: parent.verticalCenter
            }

            Label {
                id: header
                verticalAlignment: Text.AlignVCenter
                width: parent.width - icon.width
                horizontalAlignment: Text.AlignRight
                font.pixelSize: Theme.fontSizeSmall
                color: Theme.highlightColor
            }
        }

        Text {
            text: contentText
            font.pixelSize: Theme.fontSizeSmall
            color: Theme.primaryColor
            width: parent.width
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            visible: !clickable && !list
        }

        BackgroundItem {
            id: bgItem
            height: Theme.itemSizeExtraSmall
            anchors.left: parent.left
            anchors.leftMargin: -Theme.paddingLarge
            anchors.right: parent.right
            anchors.rightMargin: -Theme.paddingLarge
            visible: clickable
            Label {
                id: mergedText
                text: contentText
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
            onClicked: root.clicked()
        }

        Repeater {
            id: rep
            visible: list
            height: count * Theme.itemSizeExtraSmall
            anchors.left: parent.left
            anchors.right: parent.right
            delegate: BackgroundItem {
                height: Theme.itemSizeExtraSmall
                anchors.left: rep.left
                anchors.leftMargin: -Theme.paddingLarge
                anchors.right: rep.right
                anchors.rightMargin: -Theme.paddingLarge
                Label {
                    id: succOfText
                    width: parent.width
                    maximumLineCount: 1
                    truncationMode: TruncationMode.Fade
                    text: qsTr("%1 - %2 %3").arg(model.sign).arg(model.type).arg(model.name)
                    font.pixelSize: Theme.fontSizeSmall
                    color: parent.highlighted ? Theme.highlightColor : Theme.primaryColor
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.leftMargin: Theme.paddingLarge
                    anchors.rightMargin: Theme.paddingLarge
                }
                onClicked: root.modelClicked(model.itemId)
            }
        }
    }
}
