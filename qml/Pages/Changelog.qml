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

Page {
    id: about

    property string _RICHTEXT_STYLESHEET_PREAMBLE: "<html><style>a { text-decoration: none; color: '" + Theme.secondaryHighlightColor + "' }</style><body>";
    property string _RICHTEXT_STYLESHEET_APPENDIX: "</body></html>";

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
                version: "1.2.2"
                time: 1394113343000
                onExpand: v122.visible = !v122.visible
            }

            ClEntry {
                id: v122
                text: "<ul>
                        <li>Fixed: overlapping animations in the settings</li>
                        <li>Fixed: try to improve main/countries view performance</li>
                        <li>Fixed: prevent deleting favourite, when other deletion is in progress</li>
                      </ul>"
            }

            ClHeader {
                version: "1.2.1"
                time: 1393622012000
                onExpand: v121.visible = !v121.visible
            }

            ClEntry {
                id: v121
                text: _RICHTEXT_STYLESHEET_PREAMBLE + "<ul>
                        <li>Changed: application cover displays more information and has some actions</li>
                        <li>Changed: improve Wikipedia webview</li>
                        <li>Changed: redesigned database update in settings</li>
                        <li>New: added changelog page to about page</li>
                        <li>Fixed: start searching with first letter, fixing <a href='https://github.com/Buschtrommel/Chennzeihhan/issues/1'>issue #1</la></li>
                    </ul>" + _RICHTEXT_STYLESHEET_APPENDIX
            }


            ClHeader {
                version: "1.2.0"
                time: 1393373566000
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
