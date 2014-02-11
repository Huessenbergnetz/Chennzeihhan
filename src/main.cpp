//#ifdef QT_QML_DEBUG
//#include <QtQuick>
//#endif

#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <QLocale>
#include <QTranslator>

#include <sailfishapp.h>
#include "globals.h"
#include "dbmanager.h"
#include "demodel.h"
#include "deitemmodel.h"
#include "deantecessormodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication* app = SailfishApp::application(argc, argv);

    QString locale = QLocale::system().name();
    QTranslator *translator = new QTranslator;
    if ((translator->load("chennzeihhan_"+locale, ":/")))
        app->installTranslator(translator);

    DbManager dbman;
    dbman.openDB();

    DeModel *deModel = new DeModel();
    DeItemModel *deItemModel = new DeItemModel();
    DeAntecessorModel *deAntecessorModel = new DeAntecessorModel();

    QQuickView* view = SailfishApp::createView();

    view->rootContext()->setContextProperty("deModel", deModel);
    view->rootContext()->setContextProperty("deItemModel", deItemModel);
    view->rootContext()->setContextProperty("deAntecessorModel", deAntecessorModel);
    view->rootContext()->setContextProperty("versionString", VERSION_STRING);

    view->setSource(QUrl::fromLocalFile("/usr/share/harbour-chennzeihhan/qml/harbour-chennzeihhan.qml"));
    view->show();

    return app->exec();
}

