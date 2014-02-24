import QtQuick 2.0

ListModel {
    id: countriesModel
    ListElement { name: ""; code: "at"; sign: "A"; dbRevision: 3 }
    ListElement { name: ""; code: "ch"; sign: "CH"; dbRevision: 1 }
    ListElement { name: ""; code: "de"; sign: "D"; dbRevision: 1 }
    Component.onCompleted: {
        countriesModel.get(0).name = qsTr("Austria")
        countriesModel.get(1).name = qsTr("Switzerland")
        countriesModel.get(2).name = qsTr("Germany")
    }
}
