import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Delegates"
import "../Common"


Page {
    id: countryView
    objectName: "CountryView"

    property string title
    property string code
    property string colors
    property string searchString
    property string sign
    property int searchTarget: 0
    property int sortType: 0
    property int type

    onSortTypeChanged: countryModel.refresh(code, sortType, searchTarget, searchString)
    onSearchStringChanged: countryModel.refresh(code, sortType, searchTarget, searchString)
    onSearchTargetChanged: countryModel.refresh(code, sortType, searchTarget, searchString)

    Component.onCompleted: {
        searchTarget = config.get("display/search", 0)
        sortType = config.get("display/ordering", 0)
        countryModel.refresh(code, sortType, searchTarget, searchString)
    }
    onStatusChanged: {
        coverConnector.countryName = countryView.title
        coverConnector.countrySign = countryView.sign
        coverConnector.countryColors = countryView.colors
    }

    SilicaListView {
        id: listView
        anchors { top: parent.top; left: parent.left; right: parent.right; bottom: type === 1 ? searchField.top : parent.bottom }
        clip: true

        header: PageHeader { width: listView.width; title: countryView.title }

        PullDownMenu {
            visible: countryView.type === 1
            enabled: countryView.type === 1
            MenuItem {
                text: searchTarget === 0 ? qsTr("Search Target: Sign") : searchTarget === 1 ? qsTr("Search Target: Name") : qsTr("Search Target: Sign and Name")
                onClicked: {
                    var dialog = pageStack.push("../Dialogs/SearchTarget.qml")
                    dialog.accepted.connect(function() {searchTarget = dialog.searchTarget})
                }
            }
            MenuItem {
                id: sorting
                text: sortType === 0 ? qsTr("Sorting: Sign") : qsTr("Sorting: Name")
                onClicked: {
                    var dialog = pageStack.push("../Dialogs/Sorting.qml")
                    dialog.accepted.connect(function() {sortType = dialog.sorting})
                }
            }
        }

        delegate: CountryDelegate { countryCode: code; search: searchString; target: searchTarget }

        model: countryModel

        VerticalScrollDecorator {}

        FancyScroller {}

        ViewPlaceholder {
            enabled: type === 2
            text: qsTr("Information to the local breakdown of the vehicle registration plate system in %1 will be part of the premium version.").arg(title)
        }

        ViewPlaceholder {
            enabled: type === 0
            text: qsTr("The vehicle registration plate system of %1 does not use a breakdown into districts, regions or something similar. The premium version will contain further information. ").arg(title)
        }
    }

    SearchField {
        id: searchField
        width: parent.width
        anchors { bottom: parent.bottom }
        visible: countryView.type === 1
        placeholderText: qsTr("Search")
        EnterKey.onClicked: searchField.focus = false
        EnterKey.iconSource: "image://theme/icon-m-enter-close"

        Binding {
            target: countryView
            property: "searchString"
            value: searchField.text
        }
    }
}
