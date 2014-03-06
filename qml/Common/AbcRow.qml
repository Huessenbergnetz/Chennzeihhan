import QtQuick 2.0

Item  {
    id: root
    width: parent.width
    height: 108
    property variant cont
    property string cha

    signal clicked(string txt)

    Component.onCompleted: listModel.fill()

    Row {
        height: parent.height
        anchors { left: parent.left; right: parent.right }
        Repeater {
            height: root.height
            model: listModel
            delegate: AbcItem {
                text: model.text
                showBg: root.cha !== text
                onClicked: root.clicked(text)
            }
        }
    }

    ListModel {
        id: listModel
        property variant characters: cont

        function fill() {
            for (var index = 0; index < characters.length; index++) {
                append({ "text": characters[index] })
            }
        }
    }
}
