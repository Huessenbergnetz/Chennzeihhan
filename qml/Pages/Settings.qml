import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: settings

    property bool checkingDBVersion: false
    property int localDbVersion: dlMan.getLocalDBVersion()
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
        id: singleItem
        anchors.fill: parent
        contentHeight: settingsCol.height
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
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                visible: localDbVersion === 0 && remoteDbVersion === 0 && !getVersionBusy.visible
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

            Row {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                visible: (localDbVersion > 0 || remoteDbVersion > 0) && !downloadDBProgress.visible
                add: Transition { AddAnimation {} }

                Column {
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

                Item {
                    visible: checkingDBVersion
                    width: parent.width - parent.width/4
                    height: parent.height

                    BusyIndicator {
                        anchors.centerIn: parent
                        id: checkingDbBI
                        size: BusyIndicatorSize.Medium
                        running: checkingDBVersion
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
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                visible: remoteDbVersion > 0 && remoteDbVersion > localDbVersion && localDbVersion > 0
                opacity: visible ? 1 : 0
                wrapMode: Text.WordWrap
                text: qsTr("Changes in this version:")
                Behavior on opacity { FadeAnimation {} }
            }

            Text {
                id: changelogText
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.RichText
                visible: remoteDbVersion > 0 && remoteDbVersion > localDbVersion && localDbVersion > 0
                wrapMode: Text.WordWrap
                color: Theme.primaryColor
            }

            SectionHeader { text: qsTr("Display") }

            ComboBox {
                id: sortOrdering
                width: parent.width
                label: qsTr("Default ordering")

                currentIndex: config.get("display/ordering", 0)

                menu: ContextMenu {
                    MenuItem { text: qsTr("Code") }
                    MenuItem { text: qsTr("Name") }
                }

                onCurrentIndexChanged: config.set("display/ordering", currentIndex)
            }

            ComboBox {
                id: searchTarget
                width: parent.width
                label: qsTr("Default search")

                currentIndex: config.get("display/search", 0)

                menu: ContextMenu {
                    MenuItem { text: qsTr("Code") }
                    MenuItem { text: qsTr("Name") }
                    MenuItem { text: qsTr("Both") }
                }

                onCurrentIndexChanged: config.set("display/search", currentIndex)
            }
        }
    }
}
