import QtQuick 2.0
import Sailfish.Silica 1.0

Page {
    id: about

    SilicaFlickable {
        anchors.fill: parent
        contentHeight: aboutCol.height + Theme.paddingLarge
        VerticalScrollDecorator {}

        Column {
            id: aboutCol
            anchors { left: parent.left; right: parent.right }
            PageHeader { title: qsTr("Changelog") }
            move: Transition { NumberAnimation { properties: "y"; easing.type: Easing.InOutQuad } }
            add: Transition { AddAnimation {} }

            ClHeader {
                version: "1.2.0"
                time: 1393459966000
                onExpand: v120.visible = !v120.visible
            }

            ClEntry {
                id: v120
                text: "<ul>
                        <li>NEW: international vehicle registration codes</li>
                        <li>NEW: Austrian vehicle registration codes</li>
                        <li>NEW: favourites for faster access to countries</li>
                        <li>NEW: colored international signs</li>
                        <li>NEW: laod localized Wikipedia page if available, English as first fallback, otherwise native language</li>
                        <li>Changed: redesigned starting page</li>
                    </ul>"
            }

            ClHeader {
                version: "1.1.0"
                time: 1392660826000
                onExpand: v110.visible = !v110.visible
            }

            ClEntry {
                id: v110
                text: "<ul>
                        <li>NEW: database is not part of application package anymore, therefore it can be updated seperately</li>
                        <li>Changed: visual improvements</li>
                        <li>Fixed: user data paths according to Jolla harbour rules</li>
                    </ul>"
            }

            ClHeader {
                version: "1.0.0"
                time: 1392218266000
                onExpand: v100.visible = !v100.visible
            }

            ClEntry {
                id: v100
                text: "<ul><li>Initial version</li></ul>"
            }
        }
    }
}
