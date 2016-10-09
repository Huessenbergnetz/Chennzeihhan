#include "extendeditem.h"
#include "simpleitemmodel.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs a new ExtendedItem object.
 */
ExtendedItem::ExtendedItem(QObject *parent) :
    Item(parent), m_antecessors(new SimpleItemModel(this)), m_successorId(0), m_tpoId(0)
{

}


/*!
 * \brief Deconstructs the ExtendedItem object.
 */
ExtendedItem::~ExtendedItem()
{
}


/*!
 * \property ExtendedItem::antecessors
 * \brief The antecessors property.
 *
 * \par Access functions:
 * <TABLE><TR><TD>SimpleItemModel*</TD><TD>antecessors() const</TD></TR></TABLE>
 */


SimpleItemModel *ExtendedItem::antecessors() const { return m_antecessors; }



/*!
 * \property ExtendedItem::successor
 * \brief Name of the successor district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>successor() const</TD></TR><TR><TD>void</TD><TD>setSuccessor(const QString &nSuccessor)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>successorChanged(const QString &successor)</TD></TR></TABLE>
 */


QString ExtendedItem::successor() const { return m_successor; }

void ExtendedItem::setSuccessor(const QString &nSuccessor)
{
    if (nSuccessor != m_successor) {
        m_successor = nSuccessor;
#ifdef QT_DEBUG
        qDebug() << "Changed successor to" << m_successor;
#endif
        emit successorChanged(successor());
    }
}




/*!
 * \property ExtendedItem::successorId
 * \brief Database ID of the successor.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>successorId() const</TD></TR><TR><TD>void</TD><TD>setSuccessorId(uint nSuccessorId)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>successorIdChanged(uint successorId)</TD></TR></TABLE>
 */


uint ExtendedItem::successorId() const { return m_successorId; }

void ExtendedItem::setSuccessorId(uint nSuccessorId)
{
    if (nSuccessorId != m_successorId) {
        m_successorId = nSuccessorId;
#ifdef QT_DEBUG
        qDebug() << "Changed successorId to" << m_successorId;
#endif
        emit successorIdChanged(successorId());
    }
}




/*!
 * \property ExtendedItem::tpo
 * \brief Today part of this district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>tpo() const</TD></TR><TR><TD>void</TD><TD>setTpo(const QString &nTpo)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>tpoChanged(const QString &tpo)</TD></TR></TABLE>
 */


QString ExtendedItem::tpo() const { return m_tpo; }

void ExtendedItem::setTpo(const QString &nTpo)
{
    if (nTpo != m_tpo) {
        m_tpo = nTpo;
#ifdef QT_DEBUG
        qDebug() << "Changed tpo to" << m_tpo;
#endif
        emit tpoChanged(tpo());
    }
}




/*!
 * \property ExtendedItem::tpoId
 * \brief Database ID of the district this district is today part of.
 *
 * \par Access functions:
 * <TABLE><TR><TD>uint</TD><TD>tpoId() const</TD></TR><TR><TD>void</TD><TD>setTpoId(uint nTpoId)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>tpoIdChanged(uint tpoId)</TD></TR></TABLE>
 */


uint ExtendedItem::tpoId() const { return m_tpoId; }

void ExtendedItem::setTpoId(uint nTpoId)
{
    if (nTpoId != m_tpoId) {
        m_tpoId = nTpoId;
#ifdef QT_DEBUG
        qDebug() << "Changed tpoId to" << m_tpoId;
#endif
        emit tpoIdChanged(tpoId());
    }
}


/*!
 * \property ExtendedItem::optionalSigns
 * \brief List of optional signs.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>optionalSigns() const</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>optionalSignsChanged(const QString &optionalSigns)</TD></TR></TABLE>
 */


QString ExtendedItem::optionalSigns() const { return m_optionalSigns; }

void ExtendedItem::setOptionalSigns(const QString &nOptionalSigns)
{
    if (nOptionalSigns != m_optionalSigns) {
        m_optionalSigns = nOptionalSigns;
#ifdef QT_DEBUG
        qDebug() << "Changed optionalSigns to" << m_optionalSigns;
#endif
        emit optionalSignsChanged(optionalSigns());
    }
}





void ExtendedItem::clear()
{
    Item::clear();
    if (m_antecessors) {
        m_antecessors->clear();
    }
    m_successor.clear();
    emit successorChanged(m_successor);
    m_successorId = 0;
    emit successorIdChanged(0);
    m_tpo.clear();
    emit tpoChanged(m_tpo);
    m_tpoId = 0;
    emit tpoIdChanged(0);
    m_optionalSigns.clear();
    emit optionalSignsChanged(m_optionalSigns);
}

