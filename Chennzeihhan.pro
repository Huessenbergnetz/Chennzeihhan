TARGET = harbour-chennzeihhan

CONFIG += sailfishapp
QT += core sql

SOURCES += \
    src/main.cpp \
    src/dbmanager.cpp \
    src/deitemmodel.cpp \
    src/demodel.cpp \
    src/deantecessormodel.cpp \
    src/helper.cpp

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
    qml/Delegates/CountryDelegate.qml \
    qml/Views/ItemView.qml \
    l10n/chennzeihhan_en.ts \
    l10n/chennzeihhan_de.ts \
    data/carplates.sqlite \
    qml/Views/ItemWebView.qml \
    images/countries/de.png

HEADERS += \
    src/dbmanager.h \
    src/globals.h \
    src/deitemmodel.h \
    src/demodel.h \
    src/deantecessormodel.h \
    src/helper.h

RESOURCES += \
    l10n/translations.qrc

