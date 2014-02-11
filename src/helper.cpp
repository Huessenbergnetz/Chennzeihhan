#include "helper.h"

Helper::Helper(QObject *parent) :
    QObject(parent)
{
}


QString Helper::getState(int state)
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
    default:
        value = tr("Unknown");
        break;
    }

    return value;
}


QString Helper::getType(int type)
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
    case 10:
        value = tr("Members of the");
        break;
    case 11:
        value = tr("Officials of the");
        break;
    default:
        value = "";
        break;
    }

    return value;
}
