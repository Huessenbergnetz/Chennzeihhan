//#ifdef QT_QML_DEBUG
//#include <QtQuick>
//#endif

#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QSettings>
#include <QDebug>

#include <sailfishapp.h>
#include "globals.h"
#include "dbmanager.h"
#include "downloadmanager.h"
#include "wikipedia.h"
#include "configuration.h"
#include "models/countrymodel.h"
#include "models/antecessormodel.h"
#include "models/itemmodel.h"
#include "models/countriesmodel.h"


int main(int argc, char *argv[])
{
    QGuiApplication* app = SailfishApp::application(argc, argv);

    app->setOrganizationName("harbour-chennzeihhan");
    app->setOrganizationDomain("buschmann23.de");
    app->setApplicationName("harbour-chennzeihhan");
    app->setApplicationVersion(VERSION_STRING);

    QDir().mkpath(QDir::homePath().append(DATA_DIR));


    QString locale = QLocale::system().name();
    QTranslator *translator = new QTranslator;
    if ((translator->load("chennzeihhan_"+locale, "/usr/share/harbour-chennzeihhan/translations")))
        app->installTranslator(translator);

    DbManager dbman;
    dbman.checkDB();

    DownloadManager dlManager;
    Wikipedia wikipedia;
    Configuration config;

    QObject::connect(&dlManager, SIGNAL(dbDownloadStarted()), &dbman, SLOT(closeDB()));

    CountriesModel *countriesModel = new CountriesModel();
    CountriesModel *countriesSearch = new CountriesModel();
    CountriesModel *countriesFavourites = new CountriesModel();
    CountryModel *countryModel = new CountryModel();
    ItemModel *itemModel = new ItemModel();

    AntecessorModel *antecessorModel = new AntecessorModel();

    QQuickView* view = SailfishApp::createView();

    view->rootContext()->setContextProperty("dbMan", &dbman);
    view->rootContext()->setContextProperty("dlMan", &dlManager);
    view->rootContext()->setContextProperty("wp", &wikipedia);
    view->rootContext()->setContextProperty("config", &config);
    view->rootContext()->setContextProperty("countriesModel", countriesModel);
    view->rootContext()->setContextProperty("countriesFavourites", countriesFavourites);
    view->rootContext()->setContextProperty("countriesSearch", countriesSearch);
    view->rootContext()->setContextProperty("countryModel", countryModel);
    view->rootContext()->setContextProperty("itemModel", itemModel);
    view->rootContext()->setContextProperty("antecessorModel", antecessorModel);
    view->rootContext()->setContextProperty("versionString", VERSION_STRING);

    view->setSource(QUrl::fromLocalFile("/usr/share/harbour-chennzeihhan/qml/harbour-chennzeihhan.qml"));
    view->show();

    return app->exec();
}

