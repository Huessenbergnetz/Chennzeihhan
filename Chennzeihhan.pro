TARGET = harbour-chennzeihhan

CONFIG += sailfishapp
QT += core sql xml

SOURCES += \
    src/main.cpp \
    src/dbmanager.cpp \
    src/models/deantecessormodel.cpp \
    src/models/dehelper.cpp \
    src/models/countrymodel.cpp \
    src/models/itemmodel.cpp \
    src/downloadmanager.cpp \
    src/wikipedia.cpp \
    src/models/athelper.cpp \
    src/models/antecessormodel.cpp \
    src/models/countriesmodel.cpp \
    src/globals.cpp \
    src/configuration.cpp \
    src/models/languagemodel.cpp \
    src/models/languagemodelfilter.cpp

translations.path = /usr/share/harbour-chennzeihhan/translations
translations.files = l10n/*.qm
INSTALLS += translations

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
    qml/Delegates/CountriesDelegate.qml \
    qml/Views/CountryView.qml \
    l10n/chennzeihhan_en.ts \
    l10n/chennzeihhan_de.ts \
    data/carplates.sqlite \
    qml/ItemViews/ItemWebView.qml \
    qml/Delegates/CountryDelegate.qml \
    qml/ItemViews/de.qml \
    qml/ItemViews/ch.qml \
    qml/Pages/CoverPage.qml \
    qml/Pages/About.qml \
    images/harbour-chennzeihhan-256.png \
    harbour-chennzeihhan.png \
    harbour-chennzeihhan.svg \
    qml/ItemViews/ItemEntry.qml \
    qml/Common/CountryPlate.qml \
    qml/Pages/Settings.qml \
    qml/ItemViews/at.qml \
    qml/Common/AbcItem.qml \
    qml/Pages/Help.qml \
    qml/Dialogs/Sorting.qml \
    qml/Dialogs/SearchTarget.qml \
    qml/Common/AbcRow.qml \
    qml/Common/SignGrid.qml \
    qml/BTComponents/AboutPage.qml \
    qml/BTComponents/Changelog.qml \
    qml/BTComponents/ChangelogDelegate.qml \
    qml/BTComponents/ComboBoxList.qml \
    qml/BTComponents/Contributors.qml \
    qml/BTComponents/ContributorsDelegate.qml \
    qml/BTComponents/FirstStartInfo.qml \
    qml/BTComponents/PaypalChooser.qml \
    qml/Models/ContributorsModel.qml \
    qml/Models/ChangelogModel.qml \
    qml/Pages/LanguageChooser.qml

HEADERS += \
    src/dbmanager.h \
    src/globals.h \
    src/models/deantecessormodel.h \
    src/models/dehelper.h \
    src/models/countrymodel.h \
    src/models/itemmodel.h \
    src/downloadmanager.h \
    src/wikipedia.h \
    src/models/athelper.h \
    src/models/antecessormodel.h \
    src/models/countriesmodel.h \
    src/configuration.h \
    src/models/languagemodel.h \
    src/models/languagemodelfilter.h
