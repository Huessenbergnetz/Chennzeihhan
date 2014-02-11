import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
import "../Delegates"

Page {
    id: mainView

    SilicaGridView {
        id: listView
        anchors.fill: parent
        cellWidth: 180; cellHeight: 150

        header: PageHeader { width: listView.width; title: "Chennzeihhan" }

        model: CountriesModel {}

        delegate: CountriesDelegate {}
    }
}
