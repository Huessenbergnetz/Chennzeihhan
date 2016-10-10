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

import QtQuick 2.2
import Sailfish.Silica 1.0
import harbour.chennzeihhan 1.0

Page {
    id: settings

    property bool checkingDBVersion: false
    property int localDbVersion: config.databaseVersion
    property int remoteDbVersion: 0

    Connections {
        target: dlMan
        onGotDBVersion: { localDbVersion = oldVersion; remoteDbVersion = newVersion; changelogText.text = changelog; dlSize.text = cSize; instSize.text = uSize; checkingDBVersion = false }
        onDbDownloadFinished: localDbVersion = dlMan.getLocalDBVersion()
    }

    Timer {
        id: checkUpdateTimer; interval: 500; running: false; repeat: false
        onTriggered: dlMan.getOnlineDBVersion()
    }

    Timer {
        id: downloadDbTimer; interval: 500; running: false; repeat: false
        onTriggered: dlMan.downloadDB()
    }

    SilicaFlickable {
        id: settingsFlick
        anchors.fill: parent
        contentHeight: settingsCol.height + displayCol.height
        VerticalScrollDecorator {}

        PullDownMenu {
            id: pulley
            MenuItem {
                text: qsTr("Check for new database version")
                enabled: !checkingDBVersion
                visible: (localDbVersion === remoteDbVersion) || remoteDbVersion === 0
                onClicked: { checkingDBVersion = true; checkUpdateTimer.restart() }
            }
            MenuItem {
                text: qsTr("Download new database version")
                visible: (remoteDbVersion > localDbVersion)
                onClicked: { visible = false; downloadDBProgress.visible = true; downloadDbTimer.restart() }
            }
        }

        Column {
            id: settingsCol
            anchors { left: parent.left; right: parent.right }
            spacing: 5
            move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
            add: Transition { AddAnimation {} }
            PageHeader { title: qsTr("Settings") }

            SectionHeader { text: qsTr("Database") }

            Label {
                anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin }
                textFormat: Text.PlainText
                visible: localDbVersion === 0 && remoteDbVersion === 0 && !checkingDBVersion
                wrapMode: Text.WordWrap
                text: qsTr("Currently there is no database installed. Please use the pully menu to check for new DB version.")
            }

            ProgressBar {
                id: downloadDBProgress
                anchors { left: parent.left; right: parent.right }
                visible: false
                minimumValue: 0
                indeterminate: maximumValue === 1.0
                Connections {
                    target: dlMan
                    onDbDownloadProgress: { downloadDBProgress.progressValue = rec; downloadDBProgress.maximumValue = tot}
                    onDbDownloadFailed: { downloadDBProgress.visible = false }
                    onDbDownloadFinished: downloadDBProgress.visible = false
                }
            }

            Item {
                visible: settings.checkingDBVersion
                width: parent.width
                height: checkingDbBI.height

                BusyIndicator {
                    id: checkingDbBI
                    anchors.centerIn: parent
                    size: BusyIndicatorSize.Medium
                    running: visible
                    visible: settings.checkingDBVersion
                }
            }

            Row {
                anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin }
                visible: (localDbVersion > 0 || remoteDbVersion > 0) && !downloadDBProgress.visible && !settings.checkingDBVersion
                add: Transition { AddAnimation {} }

                Column {
                    id: localDbCol
                    width: parent.width / 4

                    Image {
                        width: 64; height: 64
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "image://theme/icon-m-device"
                    }

                    Text {
                        textFormat: Text.PlainText
                        text: qsTr("Rev.") + " " + localDbVersion
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Theme.primaryColor
                    }
                }

                Column {
                    width: parent.width / 4
                    visible: !checkingDbBI.visible && remoteDbVersion > 0 ? 1 : 0

                    Image {
                        width: 64; height: 64
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "image://theme/icon-m-region"
                    }

                    Text {
                        textFormat: Text.PlainText
                        text: qsTr("Rev.") + " " + remoteDbVersion
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: remoteDbVersion > localDbVersion ? Theme.highlightColor : Theme.primaryColor
                    }
                }

                Column {
                    width: parent.width / 4
                    visible: !checkingDbBI.visible && remoteDbVersion > 0 ? 1 : 0

                    Image {
                        width: 64; height: 64
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "image://theme/icon-m-mobile-network"
                    }

                    Text {
                        id: dlSize
                        textFormat: Text.PlainText
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Theme.primaryColor
                    }
                }

                Column {
                    width: parent.width / 4
                    visible: !checkingDbBI.visible && remoteDbVersion > 0 ? 1 : 0

                    Image {
                        width: 64; height: 64
                        anchors.horizontalCenter: parent.horizontalCenter
                        source: "image://theme/icon-l-storage"
                        smooth: true
                    }

                    Text {
                        id: instSize
                        textFormat: Text.PlainText
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: Theme.primaryColor
                    }
                }
            }

            Item {
                width: parent.width
                height: Theme.paddingLarge
                visible: remoteDbVersion > 0 && remoteDbVersion > localDbVersion && localDbVersion > 0
            }

            Label {
                anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin }
                textFormat: Text.PlainText
                visible: remoteDbVersion > 0 && remoteDbVersion > localDbVersion && localDbVersion > 0
                wrapMode: Text.WordWrap
                text: qsTr("Changes in this version:")
            }

            Text {
                id: changelogText
                anchors { left: parent.left; leftMargin: Theme.horizontalPageMargin; right: parent.right; rightMargin: Theme.horizontalPageMargin }
                textFormat: Text.RichText
                visible: remoteDbVersion > 0 && remoteDbVersion > localDbVersion && localDbVersion > 0
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
            }
        }

        Column {
            id: displayCol
            width: parent.width
            y: settingsCol.y + settingsCol.height + 5
            spacing: 5
            Behavior on y { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }

            SectionHeader { text: qsTr("Display") }

            ComboBox {
                id: sortOrdering
                width: parent.width
                label: qsTr("Default ordering")

//                currentIndex: config.get("display/ordering", 0)
                currentIndex: config.defaultOrderTarget

                menu: ContextMenu {
                    MenuItem { text: qsTr("Code") }
                    MenuItem { text: qsTr("Name") }
                }

//                onCurrentIndexChanged: config.set("display/ordering", currentIndex)
                onCurrentIndexChanged: config.defaultOrderTarget = currentIndex
            }

            ComboBox {
                id: searchTarget
                width: parent.width
                label: qsTr("Default search")

//                currentIndex: config.get("display/search", 0)
                currentIndex: config.defaultSearchTarget

                menu: ContextMenu {
                    MenuItem { text: qsTr("Code") }
                    MenuItem { text: qsTr("Name") }
                    MenuItem { text: qsTr("Both") }
                }

//                onCurrentIndexChanged: config.set("display/search", currentIndex)
                onCurrentIndexChanged: config.defaultSearchTarget = currentIndex
            }

            SectionHeader { text: qsTr("Display language") }

            ComboBox {
                id: langChoser
                label: qsTr("Language")
                description: qsTr("Changing the display language is only applied after a restart of the application.")
                width: parent.width
                menu: ContextMenu {
                    Repeater {
                        model: LanguageModel { id: langModel }
                        MenuItem { text: model.name; readonly property string value: model.code }
                    }
                }
                onCurrentIndexChanged: { if (currentItem) { config.displayLanguage = currentItem.value } }
                currentIndex: langModel.findIndex(config.displayLanguage)
            }
        }
    }
}
