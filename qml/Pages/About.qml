import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: about

    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

    SilicaFlickable {
        id: singleItem
        anchors.fill: parent
        contentHeight: aboutCol.height
        VerticalScrollDecorator {}

    Column {
        id: aboutCol
        anchors { left: parent.left; right: parent.right }
        spacing: 5
        PageHeader { title: qsTr("About") }

        Image {
            anchors.horizontalCenter: parent.horizontalCenter
            visible: true
            width: 256
            height: 256
            sourceSize.width: 256
            sourceSize.height: 256
            source: "/usr/share/harbour-chennzeihhan/images/harbour-chennzeihhan-256.png"
        }

        Label {
            id: labelName
            anchors.horizontalCenter: parent.horizontalCenter
            textFormat: Text.PlainText
            text: "Chennzeihhan " + versionString
        }

        Text {
            id: description
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Vehicle registation plates database for Sailfish OS")
            width: parent.width - 2 * Theme.paddingLarge
            font.weight: Font.Light
            wrapMode: Text.WordWrap
            textFormat: Text.PlainText
            color: Theme.primaryColor
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: copyright
            anchors.horizontalCenter: parent.horizontalCenter
            text: "© 2014, Buschtrommel"
            width: parent.width
            font.weight: Font.Light
            wrapMode: Text.WordWrap
            textFormat: Text.PlainText
            color: Theme.primaryColor
            horizontalAlignment: Text.AlignHCenter
        }

        Text {
            id: license
            anchors.horizontalCenter: parent.horizontalCenter
            font.weight: Font.Light
            text: _RICHTEXT_STYLESHEET_PREAMBLE + qsTr("Licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>") + _RICHTEXT_STYLESHEET_APPENDIX
            width: parent.width - 2 * Theme.paddingLarge
            textFormat: Text.RichText
            color: Theme.primaryColor
            onLinkActivated: { Qt.openUrlExternally(link) }
            horizontalAlignment: Text.AlignHCenter
        }

        Button {
            id: websiteLink
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Visit website")
            onClicked: Qt.openUrlExternally("http://www.buschmann23.de/entwicklung/anwendungen/chennzeihhan/")
        }

        Button {
            id: donationLink
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Make a donation")
            onClicked: Qt.openUrlExternally("https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=B2HKSUP3P4UR6")
        }

    }

    }
}