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
import QtWebKit 3.0
import Sailfish.Silica 1.0

Page {
    id: singleWebView
    objectName: "WikiView"

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
        visible: webView.loading && chennzeihhan.applicationActive
        running: visible
        opacity: visible ? 1 : 0
        Behavior on opacity { FadeAnimation {} }
    }

    SilicaWebView {
        id: webView
        anchors.fill: parent

        experimental.userAgent: "Mozilla/5.0 (Maemo; Linux; Jolla; Sailfish; Mobile) AppleWebKit/534.13 (KHTML, like Gecko) NokiaBrowser/8.5.0 Mobile Safari/534.13"
        experimental.preferences.pluginsEnabled: true
        experimental.preferences.javascriptEnabled: true
        experimental.preferences.defaultFontSize: Theme.fontSizeSmall

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

//    CoverActionList {
//            enabled: singleWebView.status === PageStatus.Active
//            iconBackground: true

//            CoverAction {
//                iconSource: "image://theme/icon-cover-previous"
//                onTriggered: pageStack.navigateBack(PageStackAction.Immediate)
//            }

//            CoverAction {
//                iconSource: webView.loading ? "image://theme/icon-cover-cancel" : "image://theme/icon-cover-refresh"
//                onTriggered: {
//                    if (webView.loading) {
//                        webView.stop()
//                    } else {
//                        webView.reload()
//                    }
//                }
//            }
//        }
}
