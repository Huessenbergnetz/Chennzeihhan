#include "deitem.h"
#include "simpleitem.h"
#include "simpleitemmodel.h"
#include <QSqlQuery>
#include "dehelper.h"
#ifdef QT_DEBUG
#include <QtDebug>
#include <QSqlError>
#endif

DeItem::DeItem(QObject *parent) : ExtendedItem(parent)
{
    setCountryCode(QStringLiteral("de"));
    setCountryName(tr("Germany"));
}

DeItem::~DeItem()
{

}



void DeItem::clear()
{
    ExtendedItem::clear();
}



void DeItem::query()
{
    setInOperation(true);

    clear();

    QSqlQuery q;
    if (!q.exec(QStringLiteral("SELECT sign, name, capitol, type, state, assign, successor, admin, closed, optional, wikipedia, coa FROM de WHERE id = %1").arg(id()))) {
        qCritical("Failed to perform query: %s", qPrintable(q.lastError().text()));
        setInOperation(false);
        return;
    }

    DeHelper deh;

    if (q.next()) {
        setSign(q.value(0).toString());
        setName(q.value(1).toString());
        setCapital(q.value(2).toString());
        setType(deh.getType(q.value(3).toInt()));
        setState(deh.getState(q.value(4).toInt()));
        setFounded(q.value(5).toUInt());
        setSuccessorId(q.value(6).toUInt());
        setTpoId(q.value(7).toUInt());
        setDisbanded(q.value(8).toUInt());
        setOptional(q.value(9).toUInt());
        setWikipedia(q.value(10).toString());
        setCoa(q.value(11).toString());
    }

    if (successorId() > 0) {
        if (!q.exec(QStringLiteral("SELECT name, type, sign FROM de WHERE id = %1").arg(successorId()))) {
            qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
        } else if (q.next()) {
            //: 1 - the carplate sign, 2 - the district type, 3 - the district name
            setSuccessor(tr("%1 - %2 %3").arg(q.value(2).toString(), deh.getType(q.value(1).toInt()), q.value(0).toString()));
        }
    }

    if ((tpoId() > 0) && (successorId() != tpoId())) {
        if (!q.exec(QStringLiteral("SELECT name, type, sign FROM de WHERE id = %1").arg(tpoId()))) {
            qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
        } else if (q.next()) {
            //: 1 - the carplate sign, 2 - the district type, 3 - the district name
            setTpo(tr("%1 - %2 %3").arg(q.value(2).toString(), deh.getType(q.value(1).toInt()), q.value(0).toString()));
        }
    }

    if (disbanded() == 0) {
        QStringList optSigns;
        QList<int> subOptSignIds;
        QList<int> subSubOptSignIds;
        if (q.exec(QStringLiteral("SELECT id, sign FROM de WHERE successor = %1 AND optional > 0").arg(id()))) {
            while (q.next()) {
                subOptSignIds << q.value(0).toInt();
                optSigns << q.value(1).toString();
            }

            for (int i = 0; i < subOptSignIds.size(); ++i)
            {
                if (q.exec(QStringLiteral("SELECT id, sign FROM de WHERE successor = %1 AND optional > 0").arg(subOptSignIds.at(i)))) {
                    while (q.next()) {
                        subSubOptSignIds << q.value(0).toInt();
                        optSigns << q.value(1).toString();
                    }
                } else {
                    qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
                }
            }

            for (int i = 0; i < subSubOptSignIds.size(); ++i)
            {
                if (q.exec(QStringLiteral("SELECT sign FROM de WHERE successor = %1 AND optional > 0").arg(subSubOptSignIds.at(i)))) {
                    while (q.next()) {
                        optSigns << q.value(0).toString();
                    }
                } else {
                    qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
                }
            }

            if (!optSigns.isEmpty()) {
                setOptionalSigns(optSigns.join(QStringLiteral(", ")));
            }

        } else {
            qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
        }
    }

    if (q.exec(QStringLiteral("SELECT id AS itemId, name, type, sign FROM de WHERE successor = %1").arg(id()))) {
        QList<SimpleItem*> l;
        while (q.next()) {
            l.append(new SimpleItem(q.value(0).toUInt(), q.value(1).toString(), deh.getType(q.value(2).toInt()), q.value(3).toString()));
        }
        if (!l.isEmpty() && antecessors()) {
            antecessors()->addItems(l);
        }
    } else {
        qWarning("Failed to perform query: %s", qPrintable(q.lastError().text()));
    }

    setInOperation(false);
}
