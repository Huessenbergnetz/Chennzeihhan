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

            Row {
                id: closedRow
                anchors { left: parent.left; leftMargin: Theme.paddingLarge; right: parent.right; rightMargin: Theme.paddingLarge }
                spacing: 8

                Image {
                    id: closedIco
                    width: Theme.fontSizeSmall; height: Theme.fontSizeSmall;
                    smooth: true
                    source: "image://theme/icon-s-timer"
                }

                Label {
                    id: closedDesc
                    width: parent.width - systemIco.width
                    wrapMode: Text.WordWrap
                    font.pixelSize: Theme.fontSizeSmall
                    text: qsTr("This district does not exist anymore but the code may be still in use by old registered vehicles or is now optionally available for the successor district.")
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
