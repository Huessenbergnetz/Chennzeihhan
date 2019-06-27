/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

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

import QtQuick 2.2
import Sailfish.Silica 1.0
import de.huessenbergnetz.hbnsc 1.0
import harbour.chennzeihhan 1.0
import "../Models"

AboutPage {

    appTitle: "Chennzeihhan"
    appDescription: qsTr("Vehicle registation plates database for Sailfish OS")
    appHomepage: "http://www.buschmann23.de/entwicklung/anwendungen/chennzeihhan/"
    appCopyrightHolder: "Matthias Fehring"
    appCopyrightYearFrom: "2014"
    appCopyrightYearTo: "2019"
    appLicense: "GNU General Public License, Version 2"
    appLicenseFile: "GPLv2.qml"
//    appLicense: qsTr("Source code is licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>.<br />Car plates database is licensed under <a href='http://creativecommons.org/licenses/by-nc-sa/4.0/'>Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International</a>.")

    changelogModel: ChangelogModel {}
    bugTrackerBaseUrl: "https://github.com/Huessenbergnetz/Chennzeihhan/issues/"

    contributorsAvatarBasePath: "/usr/share/harbour-chennzeihhan/images/contributors"
    contributorsModel: ContributorsModel {}

    privacyPolicyQmlFile: ""

    contactCompany: "Hüssenbergnetz"
    contactName: "Matthias Fehring"
    contactStreet: "Zum Südholz"
    contactHouseNo: "8"
    contactZIP: "34439"
    contactCity: "Willebadessen"
    contactCountry: qsTr("Germany")
    contactEmail: Qt.atob("a29udGFrdEBodWVzc2VuYmVyZ25ldHouZGU=")
    contactWebsite: "www.huessenbergnetz.de"
    contactWebsiteLink: "https://www.huessenbergnetz.de/?pk_campaign=Sailfish-App-Chennzeihhan&pk_kwd=AboutPage"

    bugUrl: "https://github.com/Huessenbergnetz/Chennzeihhan/issues/"
    translateUrl: "https://www.transifex.com/huessenbergnetz/chennzeihhan"

    licensesModel: LicensesModel {}
}
