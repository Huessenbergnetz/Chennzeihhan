import QtQuick 2.0
import "../Delegates"

GridView {
    id: root
    property alias timer: backToNonOpaque

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

    visible: false
    height: visible ? calcHeight(count / 3) * cellHeight : 0
    anchors { left: parent.left; right: parent.right }
    delegate: CountriesDelegate{}
    interactive: false
    cellWidth: 180; cellHeight: 150
    model: countriesModel
    Behavior on height { NumberAnimation { duration: 200; easing.type: Easing.InOutQuad } }
    Behavior on opacity { NumberAnimation { duration: root.opacity === 1 ? 0 : 200; easing.type: Easing.InOutQuad } }
    Timer { id: backToNonOpaque; interval: 200; onTriggered: root.opacity = 1; }
}
