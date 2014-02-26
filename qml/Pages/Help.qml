import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: about

    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: helpCol.height
        VerticalScrollDecorator {}

        Column {
            id: helpCol
            anchors { left: parent.left; right: parent.right }
            spacing: 10
            PageHeader { title: qsTr("Help") }

            SectionHeader { text: qsTr("Legend") }

            Row {
                id: favRow
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                spacing: 8

                Image {
                    id: favIco
                    width: Theme.fontSizeSmall; height: Theme.fontSizeSmall;
                    smooth: true
                    source: "image://theme/icon-s-favorite"
                }

                Label {
                    id: favDesc
                    width: parent.width - favIco.width
                    wrapMode: Text.WordWrap
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("You have marked this as a favourite for faster access.")
                }
            }

            Row {
                id: officialRow
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                spacing: 8

                Image {
                    id: officialIco
                    width: Theme.fontSizeSmall; height: Theme.fontSizeSmall;
                    smooth: true
                    source: "image://theme/icon-s-installed"
                }

                Label {
                    id: officialDesc
                    width: parent.width - officialIco.width
                    wrapMode: Text.WordWrap
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("This is an official code that appears in the UN list of distinguishing codes.")
                }
            }

            Row {
                id: systemRow
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                spacing: 8

                Image {
                    id: systemIco
                    width: Theme.fontSizeSmall; height: Theme.fontSizeSmall;
                    smooth: true
                    source: "image://theme/icon-s-group-chat"
                }

                Label {
                    id: systemDesc
                    width: parent.width - systemIco.width
                    wrapMode: Text.WordWrap
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("This country uses a deeper categorized system of registration plate code signs.")
                }
            }

            SectionHeader { text: qsTr("Help") }

            Text {
                id: helpText
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                wrapMode: Text.WordWrap
                font.pixelSize: Theme.fontSizeSmall
                text: qsTr("To add a country to the list of favourites, press and hold the list entry.")
                color: Theme.primaryColor
            }


        }
    }
}