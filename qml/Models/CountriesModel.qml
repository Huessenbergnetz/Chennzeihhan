import QtQuick 2.0

ListModel {
    id: countriesModel
    ListElement { name: ""; code: "ch"; sign: "D" }
    ListElement { name: ""; code: "de"; sign: "CH" }
    Component.onCompleted: {
        countriesModel.get(0).name = qsTr("Switzerland")
        countriesModel.get(1).name = qsTr("Germany")
    }
}
