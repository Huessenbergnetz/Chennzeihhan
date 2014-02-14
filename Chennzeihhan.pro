TARGET = harbour-chennzeihhan

CONFIG += sailfishapp
QT += core sql

SOURCES += \
    src/main.cpp \
    src/dbmanager.cpp \
    src/models/deantecessormodel.cpp \
    src/models/dehelper.cpp \
    src/models/countrymodel.cpp \
    src/models/itemmodel.cpp

datafiles.path = /usr/share/harbour-chennzeihhan/data
datafiles.files = data/*
INSTALLS += datafiles

images.path = /usr/share/harbour-chennzeihhan/images
images.files = images/*
INSTALLS += images

OTHER_FILES += \
    qml/cover/CoverPage.qml \
    rpm/Chennzeihhan.spec \
    qml/harbour-chennzeihhan.qml \
    harbour-chennzeihhan.desktop \
    rpm/harbour-chennzeihhan.yaml \
    qml/Views/MainView.qml \
    qml/Models/CountriesModel.qml \
    qml/Delegates/CountriesDelegate.qml \
    qml/Views/CountryView.qml \
    l10n/chennzeihhan_en.ts \
    l10n/chennzeihhan_de.ts \
    data/carplates.sqlite \
    qml/Views/ItemWebView.qml \
    images/countries/de.png \
    qml/Delegates/CountryDelegate.qml \
    qml/ItemViews/de.qml \
    qml/ItemViews/ch.qml \
    qml/Common/FancyScroller.qml \
    qml/Pages/CoverPage.qml \
    qml/Pages/About.qml \
    images/countries/ch.png \
    images/harbour-chennzeihhan-256.png \
    harbour-chennzeihhan.png \
    harbour-chennzeihhan.svg \
    qml/ItemViews/ItemEntry.qml

HEADERS += \
    src/dbmanager.h \
    src/globals.h \
    src/models/deantecessormodel.h \
    src/models/dehelper.h \
    src/models/countrymodel.h \
    src/models/itemmodel.h

RESOURCES += \
    l10n/translations.qrc

