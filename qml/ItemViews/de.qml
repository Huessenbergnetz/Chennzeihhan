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
import Sailfish.Silica 1.0
import harbour.chennzeihhan 1.0

ExtendedItemView {
    id: deItemView
    objectName: "ItemView"

    DeItem {
        id: deItem
        coverConnector: cc
    }

    property alias itemId: deItem.id

    sign: deItem.sign
    //: the first one is the district type, the second is the district name
    name: qsTr("%1 %2").arg(deItem.type).arg(deItem.name)
    state: deItem.state
    capital: deItem.capital
    capitalHeader: qsTr("Capital", "District capital in Germany")
    disbanded: deItem.disbanded
    founded: deItem.founded
    optional: deItem.optional
    optionalSigns: deItem.optionalSigns
    antecessors: deItem.antecessors
    successorId: deItem.successorId
    successor: deItem.successor
    tpoId: deItem.tpoId
    tpo: deItem.tpo
    wikipedia: deItem.wikipedia
    wikipediaLang: "de"
    inOperation: deItem.inOperation

    onSuccessorClicked: deItem.id = succId
    onTpoClicked: deItem.id = tpoId
    onAntecessorClicked: deItem.id = anteId
}

