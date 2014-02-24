import QtQuick 2.0
import QtWebKit 3.0
import Sailfish.Silica 1.0

Page {
    id: singleWebView

    property string itemUrl
    property string wpLang
    property string wpName

    allowedOrientations: Orientation.Landscape | Orientation.Portrait

    onStatusChanged: {
        if (status === PageStatus.Active) {
            webView.url = wp.getTranslation(wpLang, wpName)
        }
    }

    BusyIndicator {
        id: loadStatus
        z: 2
        anchors { top: parent.top; topMargin: 16; horizontalCenter: parent.horizontalCenter }
        visible: webView.loading
        running: visible
        opacity: visible ? 1 : 0
        Behavior on opacity { FadeAnimation {} }
    }

    SilicaWebView {
        id: webView
        anchors.fill: parent

        experimental.userAgent: "Mozilla/5.0 (Maemo; Linux; Jolla; Sailfish; Mobile) AppleWebKit/534.13 (KHTML, like Gecko) NokiaBrowser/8.5.0 Mobile Safari/534.13"

        PullDownMenu {
            MenuItem {
                text: webView.loading ? qsTr("Stop loading") : qsTr("Reload")
                onClicked: webView.loading ? webView.stop() : webView.reload()
            }
            MenuItem {
                text: qsTr("Open in browser")
                onClicked: Qt.openUrlExternally(webView.url)
            }
            MenuItem {
                text: qsTr("Back")
                onClicked: pageStack.popAttached()
            }
        }
    }
}