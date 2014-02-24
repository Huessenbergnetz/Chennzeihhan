#include "athelper.h"

AtHelper::AtHelper(QObject *parent) :
    QObject(parent)
{
}


QString AtHelper::getState(int state)
{
    QString value;

    switch(state) {
    case 0:
        value = tr("Austria");
        break;
    case 1:
        value = tr("Burgenland");
        break;
    case 2:
        value = tr("Carinthia");
        break;
    case 3:
        value = tr("Lower Austria");
        break;
    case 4:
        value = tr("Upper Austria");
        break;
    case 5:
        value = tr("Salzburg");
        break;
    case 6:
        value = tr("Styria");
        break;
    case 7:
        value = tr("Tyrol");
        break;
    case 8:
        value = tr("Vorarlberg");
        break;
    case 9:
        value = tr("Vienna");
        break;
    default:
        value = tr("Unknown");
        break;
    }

    return value;
}



QString AtHelper::getType(int type)
{
    QString value;

    switch (type) {
    case 0:
        value = tr("Federal Officials");
        break;
    case 1:
        value = tr("District of");
        break;
    case 2:
        value = tr("State of");
        break;
    case 3:
        value = tr("Political Expositur");
        break;
    case 4:
        value = tr("Federal Railways");
        break;
    case 5:
        value = tr("Diplomatic Corps in");
        break;
    case 6:
        value = tr("Federal Bus Service");
        break;
    case 7:
        value = tr("Postbus");
        break;
    case 8:
        value = tr("Federal Gendarmerie");
        break;
    case 9:
        value = tr("Austrian Armed Forces");
        break;
    case 10:
        value = tr("Consul in");
        break;
    case 11:
        value = tr("Federal Police");
        break;
    case 12:
        value = tr("City of");
        break;
    case 13:
        value = tr("Financial Administration");
        break;
    case 14:
        value = tr("Justice Guard");
        break;
    case 15:
        value = tr("Border Control");
        break;
    default:
        value = "";
        break;
    }

    return value;
}
