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

#include "dehelper.h"

DeHelper::DeHelper(QObject *parent) :
    QObject(parent)
{
}


QString DeHelper::getState(int state)
{
    QString value;

    switch(state) {
    case 1:
        value = tr("Baden-Württemberg");
        break;
    case 2:
        value = tr("Bavaria");
        break;
    case 3:
        value = tr("Berlin");
        break;
    case 4:
        value = tr("Brandenburg");
        break;
    case 5:
        value = tr("Bremen");
        break;
    case 6:
        value = tr("Hamburg");
        break;
    case 7:
        value = tr("Hesse");
        break;
    case 8:
        value = tr("Lower Saxony");
        break;
    case 9:
        value = tr("Mecklenburg-Vorpommern");
        break;
    case 10:
        value = tr("North Rhine-Westphalia");
        break;
    case 11:
        value = tr("Rhineland-Palatinate");
        break;
    case 12:
        value = tr("Saarland");
        break;
    case 13:
        value = tr("Saxony");
        break;
    case 14:
        value = tr("Saxony-Anhalt");
        break;
    case 15:
        value = tr("Schleswig-Holstein");
        break;
    case 16:
        value = tr("Thuringia");
        break;
    case 17:
        value = tr("Germany");
        break;
    default:
        value = tr("Unknown");
        break;
    }

    return value;
}


QString DeHelper::getType(int type)
{
    QString value;

    switch (type) {
    case 0:
        value = tr("City and District of");
        break;
    case 1:
        value = tr("District of");
        break;
    case 2:
        value = tr("City of");
        break;
    case 3:
        value = tr("Cities region");
        break;
    case 4:
        value = tr("Region of");
        break;
    case 5:
        value = tr("Regional association of");
        break;
    case 6:
        value = tr("Official cars");
        break;
    case 10:
        value = tr("Members of the");
        break;
    case 11:
        value = tr("Officials of the");
        break;
    default:
        value = QStringLiteral("");
        break;
    }

    return value;
}



bool DeHelper::isValid(const QString &assign, int closed)
{

    if (assign.contains('-') || closed > 0)
    {
        return false;
    } else {
        return true;
    }

}
