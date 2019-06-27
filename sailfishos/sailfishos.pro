TARGET = harbour-chennzeihhan

CONFIG += sailfishapp
CONFIG += c++11
QT += sql xml

SOURCES += \
    src/main.cpp \
    src/dbmanager.cpp \
    src/models/countrymodel.cpp \
    src/downloadmanager.cpp \
    src/wikipedia.cpp \
    src/configuration.cpp \
    src/models/item.cpp \
    src/models/simpleitemmodel.cpp \
    src/models/extendeditem.cpp \
    src/models/deitem.cpp \
    src/coverconnector.cpp \
    src/models/chitem.cpp \
    src/models/atitem.cpp \
    src/models/countrymodelfilter.cpp \
    src/models/alphabetmodel.cpp \
    src/models/countriesbasemodel.cpp \
    src/models/favoritesmodel.cpp \
    src/models/countriesmodelnew.cpp \
    src/models/countriesmodelfilter.cpp \
    src/models/languagesmodel.cpp \
    src/models/licensesmodel.cpp

translations.path = /usr/share/harbour-chennzeihhan/translations
translations.files = ../translations/*.qm
INSTALLS += translations

images.path = /usr/share/harbour-chennzeihhan/images
images.files = images/*
INSTALLS += images

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/Chennzeihhan.spec \
    qml/harbour-chennzeihhan.qml \
    harbour-chennzeihhan.desktop \
    rpm/harbour-chennzeihhan.yaml \
    qml/Views/MainView.qml \
    qml/Delegates/CountriesDelegate.qml \
    qml/Views/CountryView.qml \
    qml/ItemViews/ItemWebView.qml \
    qml/Delegates/CountryDelegate.qml \
    qml/ItemViews/de.qml \
    qml/ItemViews/ch.qml \
    qml/Pages/CoverPage.qml \
    qml/Pages/About.qml \
    harbour-chennzeihhan.png \
    harbour-chennzeihhan.svg \
    qml/ItemViews/ItemEntry.qml \
    qml/Common/CountryPlate.qml \
    qml/Pages/Settings.qml \
    qml/ItemViews/at.qml \
    qml/Pages/Help.qml \
    qml/Dialogs/Sorting.qml \
    qml/Dialogs/SearchTarget.qml \
    qml/Models/ContributorsModel.qml \
    qml/Models/ChangelogModel.qml \
    qml/ItemViews/SimpleItemView.qml \
    qml/ItemViews/ExtendedItemView.qml \
    qml/Views/SignGrid.qml

HEADERS += \
    src/dbmanager.h \
    src/globals.h \
    src/models/countrymodel.h \
    src/downloadmanager.h \
    src/wikipedia.h \
    src/configuration.h \
    src/models/item.h \
    src/models/simpleitemmodel.h \
    src/models/simpleitem.h \
    src/models/extendeditem.h \
    src/models/deitem.h \
    src/coverconnector.h \
    src/models/chitem.h \
    src/models/atitem.h \
    src/models/countrymodelfilter.h \
    src/models/alphabetmodel.h \
    src/models/countriesbasemodel.h \
    src/models/favoritesmodel.h \
    src/models/countriesmodelnew.h \
    src/models/countriesmodelfilter.h \
    src/models/languagesmodel.h \
    src/models/licensesmodel.h

include(../HBN_SFOS_Components/HBN_SFOS_Components.pri)
