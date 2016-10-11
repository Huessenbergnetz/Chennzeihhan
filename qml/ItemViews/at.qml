/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2016  Buschtrommel/Matthias Fehring

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

ExtendedItemView {
    id: atItemView
    objectName: "ItemView"

    AtItem {
        id: atItem
        coverConnector: cc
    }

    property alias itemId: atItem.id

    sign: atItem.sign
    //: the first one is the district type, the second is the district name
    name: qsTr("%1 %2").arg(atItem.type).arg(atItem.name)
    state: atItem.state
    capital: atItem.capital
    capitalHeader: qsTr("Capital", "District capital in Austria")
    disbanded: atItem.disbanded
    founded: atItem.founded
    optional: atItem.optional
    optionalSigns: atItem.optionalSigns
    antecessors: atItem.antecessors
    successorId: atItem.successorId
    successor: atItem.successor
    tpoId: atItem.tpoId
    tpo: atItem.tpo
    wikipedia: atItem.wikipedia
    wikipediaLang: "de"
    inOperation: atItem.inOperation

    onSuccessorClicked: atItem.id = succId
    onTpoClicked: atItem.id = tpoId
    onAntecessorClicked: atItem.id = anteId
}

