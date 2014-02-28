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
