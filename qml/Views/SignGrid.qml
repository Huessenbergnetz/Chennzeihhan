import QtQuick 2.2
import Sailfish.Silica 1.0
import "../Delegates"

GridView {
    id: grid
    height: Math.ceil(count / 3) * cellHeight
    width: parent ? parent.width : 0
    delegate: CountriesDelegate{}
    interactive: false
    cellWidth: width/3; cellHeight: cellWidth * 0.84
    model: countriesModel
}

