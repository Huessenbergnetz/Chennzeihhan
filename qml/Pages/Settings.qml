import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: settings

    property int localDbVersion: dlMan.getLocalDBVersion()
    property int remoteDbVersion: 0

    Connections {
        target: dlMan
        onGotDBVersion: { localDbVersion = oldVersion; remoteDbVersion = newVersion; getVersionBusy.running = false }
        onDbDownloadFinished: localDbVersion = dlMan.getLocalDBVersion()
    }

    SilicaFlickable {
        id: singleItem
        anchors.fill: parent
        contentHeight: aboutCol.height
        VerticalScrollDecorator {}

        PullDownMenu {
            MenuItem {
                text: qsTr("Check for new database version")
                visible: (localDbVersion === remoteDbVersion) || remoteDbVersion === 0
                onClicked: { getVersionBusy.running = true; dlMan.getOnlineDBVersion() }
            }
            MenuItem {
                text: qsTr("Download new database version")
                visible: (remoteDbVersion > localDbVersion)
                onClicked: { visible = false; downloadDBProgress.visible = true; dlMan.downloadDB() }
            }
        }

        Column {
            id: aboutCol
            anchors { left: parent.left; right: parent.right }
            spacing: 5
            PageHeader { title: qsTr("Settings") }

            SectionHeader { text: qsTr("Database") }

            BusyIndicator {
                id: getVersionBusy
                anchors.horizontalCenter: parent.horizontalCenter
                visible: running
            }

            Label {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                visible: localDbVersion === 0 && remoteDbVersion === 0 && !getVersionBusy.visible
                wrapMode: Text.WordWrap
                text: qsTr("Currently there is no database installed. Please use the pully menu to check for new DB version.")
            }

            Label {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                visible: localDbVersion > 0
                wrapMode: Text.WordWrap
                text: qsTr("Installed database revision: ") + localDbVersion
            }

            Label {
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                textFormat: Text.PlainText
                visible: remoteDbVersion > 0
                wrapMode: Text.WordWrap
                text: qsTr("Available database revision: ") + remoteDbVersion
            }

            ProgressBar {
                id: downloadDBProgress
                visible: false
                minimumValue: 0
                Connections {
                    target: dlMan
                    onDbDownloadProgress: { downloadDBProgress.progressValue = rec; downloadDBProgress.maximumValue = tot}
                    onDbDownloadFailed: { downloadDBProgress.visible = false }
                    onDbDownloadFinished: downloadDBProgress.visible = false
                }
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
