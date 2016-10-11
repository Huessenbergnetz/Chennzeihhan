/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014  Buschtrommel/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <QtQml>
#include <QGuiApplication>
#include <QQuickView>
#include <QLocale>
#include <QTranslator>
#include <QDir>
#include <QSettings>

#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#ifdef QT_DEBUG
#include <QtDebug>
#endif

#ifndef CLAZY
#include <sailfishapp.h>
#endif
#include "globals.h"
#include "dbmanager.h"
#include "downloadmanager.h"
#include "wikipedia.h"
#include "configuration.h"
#include "coverconnector.h"
#include "models/countrymodel.h"
#include "models/languagemodel.h"
#include "models/simpleitemmodel.h"
#include "models/atitem.h"
#include "models/chitem.h"
#include "models/deitem.h"
#include "models/countrymodelfilter.h"
#include "models/alphabetmodel.h"
#include "models/favoritesmodel.h"
#include "models/countriesmodelfilter.h"


int main(int argc, char *argv[])
{
#ifndef CLAZY
    QGuiApplication* app = SailfishApp::application(argc, argv);
#else
    QGuiApplication* app = new QGuiApplication(argc, argv);
#endif

    app->setOrganizationName(QStringLiteral("harbour-chennzeihhan"));
    app->setOrganizationDomain(QStringLiteral("buschmann23.de"));
    app->setApplicationName(QStringLiteral("harbour-chennzeihhan"));
    app->setApplicationVersion(QStringLiteral(VERSION_STRING));

    QDir().mkpath(QDir::homePath().append(QLatin1String(DATA_DIR)));

    DbManager dbman;
    dbman.checkDB();

    CoverConnector cc;

    Configuration config;

    QString locale = config.displayLanguage();

#ifdef QT_DEBUG
    qDebug() << "Stored locale code:" << locale;
#endif

    if (locale == QLatin1String("C")) {
        locale = QLocale::system().name();
    } else {
        QLocale::setDefault(QLocale(locale));
    }

#ifdef QT_DEBUG
    qDebug() << "Loading locale:" << locale;
#endif

#ifndef CLAZY
    QTranslator *translator = new QTranslator(app);
    if (translator->load("chennzeihhan_"+locale, SailfishApp::pathTo(QStringLiteral("translations")).toString(QUrl::RemoveScheme))) {
        app->installTranslator(translator);
    }
#endif


    qmlRegisterType<LanguageModel>("harbour.chennzeihhan", 1, 0, "LanguageModel");
    qmlRegisterType<CountryModelFilter>("harbour.chennzeihhan", 1, 0, "CountryModel");
    qmlRegisterType<Wikipedia>("harbour.chennzeihhan", 1, 0, "Wikipedia");
    qmlRegisterType<DownloadManager>("harbour.chennzeihhan", 1, 0, "DownloadManager");
    qmlRegisterUncreatableType<Chennzeihhan>("harbour.chennzeihhan", 1, 0, "Chennzeihhan", QStringLiteral("You can not create a Chennzeihhan component."));
    qmlRegisterUncreatableType<SimpleItemModel>("harbour.chennzeihhan", 1, 0, "SimpleItemModel", QStringLiteral("You can not create a SimpleItemModel component."));
    qmlRegisterUncreatableType<CoverConnector>("harbour.chennzeihhan", 1, 0, "CoverConnector", QStringLiteral("You can not create a CoverConnector component."));
    qmlRegisterUncreatableType<Configuration>("harbour.chennzeihhan", 1, 0, "Configuration", QStringLiteral("You can not create a Configuration component."));
    qmlRegisterUncreatableType<DbManager>("harbour.chennzeihhan", 1, 0, "DbManager", QStringLiteral("You can not create a DbManager component."));
    qmlRegisterType<AlphabetModel>("harbour.chennzeihhan", 1, 0, "AlphabetModel");
    qmlRegisterType<AtItem>("harbour.chennzeihhan", 1, 0, "AtItem");
    qmlRegisterType<ChItem>("harbour.chennzeihhan", 1, 0, "ChItem");
    qmlRegisterType<DeItem>("harbour.chennzeihhan", 1, 0, "DeItem");


//    CountriesModel *countriesModel = new CountriesModel();
    const QScopedPointer<CountriesModelFilter> countriesModel(new CountriesModelFilter);
//    CountriesModel *countriesSearch = new CountriesModel();
//    CountriesModel *countriesFavourites = new CountriesModel();
    const QScopedPointer<FavoritesModel> favoritesModel(new FavoritesModel(&config));
//    CountriesModel *abcModel = new CountriesModel();

#ifndef CLAZY
    QQuickView* view = SailfishApp::createView();
#else
    QQuickView* view = new QQuickView;
#endif

    view->rootContext()->setContextProperty(QStringLiteral("dbMan"), &dbman);
    view->rootContext()->setContextProperty(QStringLiteral("config"), &config);
    view->rootContext()->setContextProperty(QStringLiteral("countriesModel"), countriesModel.data());
    view->rootContext()->setContextProperty(QStringLiteral("favoritesModel"), favoritesModel.data());
//    view->rootContext()->setContextProperty(QStringLiteral("countriesSearch"), countriesSearch);
    view->rootContext()->setContextProperty(QStringLiteral("cc"), &cc);
    view->rootContext()->setContextProperty(QStringLiteral("versionString"), QStringLiteral(VERSION_STRING));
    view->rootContext()->setContextProperty(QStringLiteral("versionInt"), VERSION);

#ifndef CLAZY
    view->setSource(SailfishApp::pathTo(QStringLiteral("qml/harbour-chennzeihhan.qml")));
#endif

    view->show();

    return app->exec();
}

