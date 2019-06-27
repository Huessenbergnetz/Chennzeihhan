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

#include "licensesmodel.h"

LicensesModel::LicensesModel(QObject *parent) :
    Hbnsc::LicenseModel(parent)
{
    add(QStringLiteral("D-A-CH Carplates Database"),
        QStringLiteral("Matthias Fehring"),
        QString(),
        QUrl(QStringLiteral("https://github.com/Huessenbergnetz/Chennzeihhan")),
        tr("Car plates database providing data about car plates in Germany, Austria and Switzerland."),
        QStringLiteral("Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International Public License"),
        QStringLiteral("CC-BY-NC-SA-4_0.qml"),
        QUrl(QStringLiteral("https://github.com/Huessenbergnetz/Chennzeihhan/blob/master/LICENSE.database")),
        QUrl());

    add (QStringLiteral("Chennzeihhan Translations"),
         QStringLiteral("Chennzeihhan Translators"),
         QString(),
         QUrl(QStringLiteral("https://www.transifex.com/huessenbergnetz/chennzeihhan")),
         tr("The translations for Chennzeihhan are provided by the community. To see who is responsible for which translation, open the contributors page."),
         QStringLiteral("Creative Commons Attribution 4.0 International Public License"),
         QStringLiteral("CC-BY-4_0.qml"),
         QUrl(QStringLiteral("https://github.com/Huessenbergnetz/Chennzeihhan/blob/master/LICENSE.translations")),
         QUrl());

    sortLicenses();
}

LicensesModel::~LicensesModel()
{

}

#include "moc_licensesmodel.cpp"
