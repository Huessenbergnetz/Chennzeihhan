/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2016  Buschtrommel/Matthias Fehring

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
import "../BTComponents"
import "../Models"

AboutPage {

    appTitle: "Chennzeihhan"
    appVersion: Qt.application.version
    appDescription: qsTr("Vehicle registation plates database for Sailfish OS")
    appHomepage: "http://www.buschmann23.de/entwicklung/anwendungen/chennzeihhan/"
    appCover: "/usr/share/harbour-chennzeihhan/images/banner.png"
    appCopyright: "© 2014-2015, Buschtrommel"
    appLicense: qsTr("Source code is licensed under the <a href='http://www.gnu.org/licenses/gpl-2.0.en.html'>GNU GPL v2</a>.<br />Car plates database is licensed under <a href='http://creativecommons.org/licenses/by-nc-sa/4.0/'>Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International</a>.")

    changelogModel: ChangelogModel {}
    bugTrackerBaseUrl: "https://github.com/Buschtrommel/Chennzeihhan/issues/"

    contributorsAvatarBasePath: "/usr/share/harbour-chennzeihhan/images/contributors"
    contributorsModel: ContributorsModel {}

    privacyPolicyQmlFile: ""

    contactCompany: "Buschtrommel"
    contactName: "Matthias Fehring"
    contactStreet: "Engelhardstraße"
    contactHouseNo: "32"
    contactZIP: "81369"
    contactCity: qsTr("Munich")
    contactCountry: qsTr("Germany")
    contactEmail: "kontakt@buschmann23.de"
    contactWebsite: "www.buschmann23.de"

    bugUrl: "https://github.com/Buschtrommel/Chennzeihhan/issues/"
    translateUrl: "https://www.transifex.com/projects/p/chennzeihhan/"

    licensesModel: ListModel {
    }
}
