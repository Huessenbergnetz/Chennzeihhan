import QtQuick 2.0
import Sailfish.Silica 1.0
import "Views"

ApplicationWindow
{
    initialPage: Component { MainView { } }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")
}


