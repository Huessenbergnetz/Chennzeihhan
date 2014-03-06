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
import "../Delegates"

GridView {
    id: root

    function calcHeight(h) {
        var h1 = h;
        var h2 = Math.round(h)
        var h3
        if (h2 < h1) {
            h3 = h2 +1
        } else {
            h3 = h2;
        }
        return h3
    }

    clip: true
    visible: false
    height: visible ? calcHeight(count / 3) * cellHeight : 0
    anchors { left: parent.left; right: parent.right }
    delegate: CountriesDelegate{}
    interactive: false
    cellWidth: 180; cellHeight: 150
    model: countriesModel
}
