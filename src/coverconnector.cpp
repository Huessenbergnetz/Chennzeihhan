#include "coverconnector.h"
#ifdef QT_DEBUG
#include <QtDebug>
#endif

/*!
 * \brief Constructs a new CoverConnector object.
 */
CoverConnector::CoverConnector(QObject *parent) :
    QObject(parent)
{
    m_mode = Overview;
}


/*!
 * \brief Deconstructs the CoverConnector object.
 */
CoverConnector::~CoverConnector()
{
}


/*!
 * \property CoverConnector::country
 * \brief Name of the current country.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>country() const</TD></TR><TR><TD>void</TD><TD>setCountry(const QString &nCountry)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>countryChanged(const QString &country)</TD></TR></TABLE>
 */


QString CoverConnector::country() const { return m_country; }

void CoverConnector::setCountry(const QString &nCountry)
{
    if (nCountry != m_country) {
        m_country = nCountry;
#ifdef QT_DEBUG
        qDebug() << "Changed country to" << m_country;
#endif
        emit countryChanged(country());
    }
}




/*!
 * \property CoverConnector::name
 * \brief Name of the current district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>name() const</TD></TR><TR><TD>void</TD><TD>setName(const QString &nName)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>nameChanged(const QString &name)</TD></TR></TABLE>
 */


QString CoverConnector::name() const { return m_name; }

void CoverConnector::setName(const QString &nName)
{
    if (nName != m_name) {
        m_name = nName;
#ifdef QT_DEBUG
        qDebug() << "Changed name to" << m_name;
#endif
        emit nameChanged(name());
    }
}




/*!
 * \property CoverConnector::type
 * \brief Type of the current district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>type() const</TD></TR><TR><TD>void</TD><TD>setType(const QString &nType)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>typeChanged(const QString &type)</TD></TR></TABLE>
 */


QString CoverConnector::type() const { return m_type; }

void CoverConnector::setType(const QString &nType)
{
    if (nType != m_type) {
        m_type = nType;
#ifdef QT_DEBUG
        qDebug() << "Changed type to" << m_type;
#endif
        emit typeChanged(type());
    }
}




/*!
 * \property CoverConnector::sign
 * \brief Sign of the current district.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>sign() const</TD></TR><TR><TD>void</TD><TD>setSign(const QString &nSign)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>signChanged(const QString &sign)</TD></TR></TABLE>
 */


QString CoverConnector::sign() const { return m_sign; }

void CoverConnector::setSign(const QString &nSign)
{
    if (nSign != m_sign) {
        m_sign = nSign;
#ifdef QT_DEBUG
        qDebug() << "Changed sign to" << m_sign;
#endif
        emit signChanged(sign());
    }
}




/*!
 * \property CoverConnector::state
 * \brief Name of the state the current district belongs to.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>state() const</TD></TR><TR><TD>void</TD><TD>setState(const QString &nState)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>stateChanged(const QString &state)</TD></TR></TABLE>
 */


QString CoverConnector::state() const { return m_state; }

void CoverConnector::setState(const QString &nState)
{
    if (nState != m_state) {
        m_state = nState;
#ifdef QT_DEBUG
        qDebug() << "Changed state to" << m_state;
#endif
        emit stateChanged(state());
    }
}




/*!
 * \property CoverConnector::countryName
 * \brief Name of the country currently viewed.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>countryName() const</TD></TR><TR><TD>void</TD><TD>setCountryName(const QString &nCountryName)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>countryNameChanged(const QString &countryName)</TD></TR></TABLE>
 */


QString CoverConnector::countryName() const { return m_countryName; }

void CoverConnector::setCountryName(const QString &nCountryName)
{
    if (nCountryName != m_countryName) {
        m_countryName = nCountryName;
#ifdef QT_DEBUG
        qDebug() << "Changed countryName to" << m_countryName;
#endif
        emit countryNameChanged(countryName());
    }
}




/*!
 * \property CoverConnector::countrySign
 * \brief Sign of the country currently viewed.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QString</TD><TD>countrySign() const</TD></TR><TR><TD>void</TD><TD>setCountrySign(const QString &nCountrySign)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>countrySignChanged(const QString &countrySign)</TD></TR></TABLE>
 */


QString CoverConnector::countrySign() const { return m_countrySign; }

void CoverConnector::setCountrySign(const QString &nCountrySign)
{
    if (nCountrySign != m_countrySign) {
        m_countrySign = nCountrySign;
#ifdef QT_DEBUG
        qDebug() << "Changed countrySign to" << m_countrySign;
#endif
        emit countrySignChanged(countrySign());
    }
}




/*!
 * \property CoverConnector::countryColors
 * \brief Colors of the country currently viewed.
 *
 * \par Access functions:
 * <TABLE><TR><TD>QStringList</TD><TD>countryColors() const</TD></TR><TR><TD>void</TD><TD>setCountryColors(const QStringList &nCountryColors)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>countryColorsChanged(const QStringList &countryColors)</TD></TR></TABLE>
 */


QStringList CoverConnector::countryColors() const { return m_countryColors; }

void CoverConnector::setCountryColors(const QStringList &nCountryColors)
{
    if (nCountryColors != m_countryColors) {
        m_countryColors = nCountryColors;
#ifdef QT_DEBUG
        qDebug() << "Changed countryColors to" << m_countryColors;
#endif
        emit countryColorsChanged(countryColors());
    }
}




/*!
 * \property CoverConnector::mode
 * \brief Current mode.
 *
 * \par Access functions:
 * <TABLE><TR><TD>Mode</TD><TD>mode() const</TD></TR><TR><TD>void</TD><TD>setMode(Mode nMode)</TD></TR></TABLE>
 * \par Notifier signal:
 * <TABLE><TR><TD>void</TD><TD>modeChanged(Mode mode)</TD></TR></TABLE>
 */


CoverConnector::Mode CoverConnector::mode() const { return m_mode; }

void CoverConnector::setMode(Mode nMode)
{
    if (nMode != m_mode) {
        m_mode = nMode;
#ifdef QT_DEBUG
        qDebug() << "Changed mode to" << m_mode;
#endif
        emit modeChanged(mode());
    }
}
