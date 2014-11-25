/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

import QtQuick 2.0
import Sailfish.Silica 1.0
import "../BTComponents"
import "../Models"

AboutPage {

    appTitle: "Chennzeihhan"
    appVersion: versionString
    appDescription: qsTr("Vehicle registation plates database for Sailfish OS")
    appHomepage: "http://www.buschmann23.de/entwicklung/anwendungen/chennzeihhan/"
    appCover: "/usr/share/harbour-chennzeihhan/images/banner.png"
    appCopyright: "© 2014, Buschtrommel"
    appLicense: qsTr("Source code is licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>.<br />Car plates database is licensed under <a href='http://creativecommons.org/licenses/by-nc-sa/4.0/'>Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International</a>.")

    changelogModel: ChangelogModel {}
    bugTrackerBaseUrl: "https://github.com/Buschtrommel/Chennzeihhan/issues/"

    contributorsAvatarBasePath: "/usr/share/harbour-chennzeihhan/images/contributors"
    contributorsModel: ContributorsModel {}

    privacyPolicyQmlFile: ""

    contactCompany: "Buschtrommel"
    contactName: "Matthias Fehring"
    contactStreet: "Engelhardstraße"
    contactHouseNo: "32"
    contactZIP: "81369"
    contactCity: qsTr("Munich")
    contactCountry: qsTr("Germany")
    contactEmail: "kontakt@buschmann23.de"
    contactWebsite: "www.buschmann23.de"

    bugUrl: "https://github.com/Buschtrommel/Chennzeihhan/issues/"
    translateUrl: "https://www.transifex.com/projects/p/chennzeihhan/"

    licensesModel: ListModel {
    }
}

//import QtQuick 2.0
//import Sailfish.Silica 1.0

//Page {
//    id: about

//    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
//    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

//    SilicaFlickable {
//        anchors.fill: parent
//        contentHeight: aboutCol.height + imgCol.height + Theme.paddingLarge
//        VerticalScrollDecorator {}

//        PullDownMenu {
//            MenuItem {
//                text: qsTr("Changelog")
//                onClicked: pageStack.push("Changelog.qml")
//            }
//        }

//        Column {
//            id: imgCol
//            anchors { left: parent.left; right: parent.right }
//            spacing: 5
//            PageHeader { title: qsTr("About") }

//            Image {
//                visible: true
//                width: parent.width
//                sourceSize.width: 540
//                sourceSize.height: 270
//                source: "/usr/share/harbour-chennzeihhan/images/banner.png"
//            }

//        }

//        Column {
//            id: aboutCol
//            anchors { left: parent.left; right: parent.right; leftMargin: Theme.paddingLarge; top: imgCol.bottom; topMargin: 10 }
//            spacing: 5

//            Label {
//                id: labelName
//                textFormat: Text.PlainText
//                font.pixelSize: Theme.fontSizeLarge
//                color: Theme.highlightColor
//                text: "Chennzeihhan " + versionString
//            }

//            Text {
//                id: description
//                text:qsTr("Vehicle registation plates database for Sailfish OS")
//                width: parent.width
//                wrapMode: Text.WordWrap
//                textFormat: Text.PlainText
//                color: Theme.secondaryHighlightColor
//            }

//            Text {
//                id: copyright
//                text: "© 2014, Buschtrommel"
//                width: parent.width
//                wrapMode: Text.WordWrap
//                textFormat: Text.PlainText
//                color: Theme.primaryColor
//            }

//            SectionHeader  { text: qsTr("Licenses") }

//            Text {
//                id: codeLicense
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + qsTr("Source code is licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>") + _RICHTEXT_STYLESHEET_APPENDIX
//                width: parent.width - Theme.paddingLarge
//                textFormat: Text.RichText
//                wrapMode: Text.WordWrap
//                color: Theme.primaryColor
//                onLinkActivated: { Qt.openUrlExternally(link) }
//            }
//            Text {
//                id: dbLicense
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + qsTr("Car plates database is licensed under <a href='http://creativecommons.org/licenses/by-nc-sa/4.0/'>Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International</a>") + _RICHTEXT_STYLESHEET_APPENDIX
//                width: parent.width - Theme.paddingLarge
//                textFormat: Text.RichText
//                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
//                color: Theme.primaryColor
//                onLinkActivated: { Qt.openUrlExternally(link) }
//            }

//            SectionHeader { text: qsTr("Contact") }

//            Text {
//                id: address
//                text: "Buschtrommel<br>Matthias Fehring<br>Engelhardstraße 32<br>81369 München<br>Deutschland"
//                width: parent.width
//                wrapMode: Text.WordWrap
//                textFormat: Text.StyledText
//                color: Theme.primaryColor
//                font.pixelSize: Theme.fontSizeSmall
//            }

//            Text {
//                id: email
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + "<a href='mailto:kontakt@buschmann23.de'>kontakt@buschmann23.de</a>" + _RICHTEXT_STYLESHEET_APPENDIX
//                color: Theme.primaryColor
//                font.pixelSize: Theme.fontSizeSmall
//                textFormat: Text.RichText
//                onLinkActivated: Qt.openUrlExternally(link)
//            }

//            Text {
//                id: website
//                text: _RICHTEXT_STYLESHEET_PREAMBLE + "<a href='http://www.buschmann23.de/entwicklung/anwendungen/chennzeihhan/'>http://http://www.buschmann23.de/.../chennzeihhan/</a>" + _RICHTEXT_STYLESHEET_APPENDIX
//                color: Theme.primaryColor
//                font.pixelSize: Theme.fontSizeSmall
//                textFormat: Text.RichText
//                onLinkActivated: Qt.openUrlExternally(link)
//            }
//        }
//    }
//}
