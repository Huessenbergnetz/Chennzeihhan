/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

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

SimpleItemView {

    property alias itemId: chItem.id

    sign: chItem.sign
    name: qsTr("Canton %1").arg(chItem.name)
    capital: chItem.capital
    capitalHeader: qsTr("Capital", "District capital in Switzerland")
    wikipedia: chItem.wikipedia
    wikipediaLang: "de"

    ChItem {
        id: chItem
        coverConnector: cc
    }

}
