import QtQuick 2.0

ListModel {
    id: countriesModel
    ListElement { name: ""; code: "de" }
//    ListElement { name: ""; code: "pl" }
    Component.onCompleted: {
        countriesModel.get(0).name = qsTr("Germany")
//        countriesModel.get(1).name = qsTr("Poland")
    }
}
