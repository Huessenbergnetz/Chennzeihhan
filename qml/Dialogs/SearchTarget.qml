import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: root
    property int searchTarget
    property string name

    signal accepted()

    Column {
        anchors.fill: parent
        PageHeader { title: qsTr("Search Target") }

        BackgroundItem {
            width: parent.width
            height: Theme.itemSizeSmall

            Label {
                id: signLabel
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge; verticalCenter: parent.verticalCenter }
                text: qsTr("Sign")
            }
            onClicked: { searchTarget = 0; name = signLabel.text; root.accepted(); pageStack.pop() }
        }

        BackgroundItem {
            width: parent.width
            height: Theme.itemSizeSmall

            Label {
                id: nameLabel
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge; verticalCenter: parent.verticalCenter }
                text: qsTr("Name")
            }
            onClicked: { searchTarget = 1; name = signLabel.text; root.accepted(); pageStack.pop() }
        }

        BackgroundItem {
            width: parent.width
            height: Theme.itemSizeSmall

            Label {
                id: bothLabel
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge; verticalCenter: parent.verticalCenter }
                text: qsTr("Sign and Name")
            }
            onClicked: { searchTarget = 2; name = bothLabel.text; root.accepted(); pageStack.pop() }
        }
    }
}
