/*
    BTComponents - QML components shared between various Buschtrommel projects
    Copyright (C) 2014  Buschtrommel/Matthias Fehring
    Contact: Matthias Fehring <kontakt@buschmann23.de>

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

/*
  Types:
  0 - New
  1 - Improved/Enhanced
  2 - Fixed
  3 - Note
*/

import QtQuick 2.2

ListModel {

    ListElement {
        version: "1.2.6"
        date: 1417006768000
        entries: [
            ListElement { type: 0; issue: ""; description: "using BTComponents, improved About, Changelog and Contributors page" },
            ListElement { type: 0; issue: ""; description: "Dutch (Netherlands) translation by Heimen Stoffel" },
            ListElement { type: 0; issue: ""; description: "choose application language in the settings" },
            ListElement { type: 1; issue: ""; description: "removed FancyScroller, not used anymore" },
            ListElement { type: 1; issue: ""; description: "translation updates" }
        ]
    }

    ListElement {
        version: "1.2.5"
        date: 1394640787000
        entries: [
            ListElement { type: 2; issue: ""; description: "loading of abc grid after first DB installation" },
            ListElement { type: 2; issue: ""; description: "minor UI glitches in settings" }
        ]
    }

    ListElement {
        version: "1.2.4"
        date: 1394637539000
        entries: [
            ListElement { type: 0; issue: ""; description: "icon to indicate disbanded districts in the district list of a country" },
            ListElement { type: 2; issue: ""; description: "operation status on favourites was not cleared after canceling the deletion" },
            ListElement { type: 2; issue: ""; description: "non ASCII characters were not shown in the alphabetical grid" },
            ListElement { type: 2; issue: ""; description: "minor UI glitches" }
        ]
    }

    ListElement {
        version: "1.2.3"
        date: 1394198331000
        entries: [
            ListElement { type: 2; issue: ""; description: "when no database was installed, alphabet rows were overlaying the information" }
        ]
    }

    ListElement {
        version: "1.2.2"
        date: 1394113343000
        entries: [
            ListElement { type: 2; issue: ""; description: "overlapping animations in the settings" },
            ListElement { type: 2; issue: ""; description: "try to improve main/countries view performance" },
            ListElement { type: 2; issue: ""; description: "prevent deleting favourite, when other deletion is in progress" }
        ]
    }

    ListElement {
        version: "1.2.1"
        date: 1393622012000
        entries: [
            ListElement { type: 0; issue: ""; description: "added changelog page to about page" },
            ListElement { type: 1; issue: ""; description: "application cover displays more information and has some actions" },
            ListElement { type: 1; issue: ""; description: "improve Wikipedia webview" },
            ListElement { type: 1; issue: ""; description: "redesigned database update in settings" },
            ListElement { type: 2; issue: "1"; description: "start searching with first letter" }
        ]
    }

    ListElement {
        version: "1.2.0"
        date: 1393373566000
        entries: [
            ListElement { type: 0; issue: ""; description: "international vehicle registration codes" },
            ListElement { type: 0; issue: ""; description: "Austrian vehicle registration codes" },
            ListElement { type: 0; issue: ""; description: "favourites for faster access to countries" },
            ListElement { type: 0; issue: ""; description: "colored international signs" },
            ListElement { type: 0; issue: ""; description: "laod localized Wikipedia page if available, English as first fallback, otherwise native language" },
            ListElement { type: 1; issue: ""; description: "redesigned starting page" }
        ]
    }

    ListElement {
        version: "1.1.0"
        date: 1392660826000
        entries: [
            ListElement { type: 0; issue: ""; description: "database is not part of application package anymore, therefore it can be updated seperately" },
            ListElement { type: 1; issue: ""; description: "visual improvements" },
            ListElement { type: 2; issue: ""; description: "user data paths according to Jolla harbour rules" }
        ]
    }

    ListElement {
        version: "1.0.0"
        date: 1392218266000
        entries: [
            ListElement { type: 0; issue: ""; description: "initial version" }
        ]
    }
}
