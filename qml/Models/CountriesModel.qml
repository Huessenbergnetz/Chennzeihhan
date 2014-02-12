import QtQuick 2.0

ListModel {
    id: countriesModel
    ListElement { name: ""; code: "ch" }
    ListElement { name: ""; code: "de" }
    Component.onCompleted: {
        countriesModel.get(0).name = qsTr("Switzerland")
        countriesModel.get(1).name = qsTr("Germany")
    }
}
