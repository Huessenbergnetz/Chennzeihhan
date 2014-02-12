import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
import "../Delegates"

Page {
    id: mainView
    objectName: "MainView"

    SilicaGridView {
        id: listView
        anchors.fill: parent
        cellWidth: 180; cellHeight: 150

        header: PageHeader { width: listView.width; title: "Chennzeihhan" }


        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("../Pages/About.qml"))
            }

        }


        model: CountriesModel {}

        delegate: CountriesDelegate {}
    }
}
