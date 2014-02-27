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
        anchors.fill: parent
        anchors.bottomMargin: searchPanel.height * 1.5

        header: PageHeader { width: listView.width; title: countryView.title }

        PullDownMenu {
            visible: type === 1
            enabled: type === 1
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

        ViewPlaceholder {
            enabled: type === 2
            text: qsTr("Information to the local breakdown of the vehicle registration plate system in %1 will be part of the premium version.").arg(title)
        }

        ViewPlaceholder {
            enabled: type === 0
            text: qsTr("The vehicle registration plate system of %1 does not use a breakdown into districts, regions or something similar. The premium version will contain further information. ").arg(title)
        }
    }

    DockedPanel {
        id: searchPanel
        width: parent.width
        height: searchField.height
        open: type === 1
        visible: open
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
