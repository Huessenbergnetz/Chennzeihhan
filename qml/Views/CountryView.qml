import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
import "../Delegates"
import "../Common"


Page {
    id: countryView

    property string title
    property string code
    property string searchString
    property int searchTarget: 0
    property int sortType: 0

    onSortTypeChanged: countryModel.refresh(code, sortType, searchTarget, searchString)
    onSearchStringChanged: countryModel.refresh(code, sortType, searchTarget, searchString)
    onSearchTargetChanged: countryModel.refresh(code, sortType, searchTarget, searchString)

    Component.onCompleted: countryModel.refresh(code, sortType, searchTarget, searchString)

    SilicaListView {
        id: listView
        anchors.fill: parent
        anchors.bottomMargin: searchPanel.height * 1.5

        header: PageHeader { width: listView.width; title: countryView.title }

        PullDownMenu {
            MenuItem {
                text: searchTarget === 0 ? qsTr("Current search: license plate") : searchTarget === 1 ? qsTr("Current search: name") : qsTr("Current search: plate and name")
                onClicked: searchTarget === 0 ? searchTarget = 1 : searchTarget === 1 ? searchTarget = 2 : searchTarget = 0
            }
            MenuItem {
                id: sorting
                text: sortType === 0 ? qsTr("Current order: license plate") : qsTr("Current order: by name")
                onClicked: sortType === 0 ? sortType = 1 : sortType = 0
            }
        }

        delegate: CountryDelegate { countryCode: code; search: searchString; target: searchTarget }

        model: countryModel

        VerticalScrollDecorator {}

        FancyScroller {}
    }

    DockedPanel {
        id: searchPanel
        width: parent.width
        height: searchField.height
        open: true
        dock: Dock.Bottom

        SearchField {
            id: searchField
            width: parent.width
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
}
