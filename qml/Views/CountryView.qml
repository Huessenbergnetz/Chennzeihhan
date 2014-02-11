import QtQuick 2.0
import Sailfish.Silica 1.0
import "../Models"
import "../Delegates"


Page {
    id: countryView

    property string title
    property string code
    property string searchString
    property int searchTarget: 0
    property int sortType: 0

    onSortTypeChanged: listView.model.refresh(sortType, searchTarget, searchString)
    onSearchStringChanged: listView.model.refresh(sortType, searchTarget, searchString)
    onSearchTargetChanged: listView.model.refresh(sortType, searchTarget, searchString)

    function getModel()
    {
        switch(code)
        {
        case "de":
            listView.model = deModel;
            deModel.refresh(sortType, searchTarget, searchString);
            break
        default:
            listView.model = deModel;
            deModel.refresh(sortType, searchTarget, searchString);
            break
        }
    }

    Component.onCompleted: getModel()

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

        model: deModel

        VerticalScrollDecorator {}

        PushUpMenu {
            enabled: listView.contentHeight >= listView.height
            visible: listView.contentHeight >= listView.height
            MenuItem {
                id: goToTop
                text: qsTr("Scroll to top")
                onClicked: listView.scrollToTop()
            }
        }
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
