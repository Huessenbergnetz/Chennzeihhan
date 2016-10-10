#ifndef COVERCONNECTOR_H
#define COVERCONNECTOR_H

#include <QObject>
#include <QStringList>

/*!
 * \brief The CoverConnector class.
 */
class CoverConnector : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString country READ country WRITE setCountry NOTIFY countryChanged)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(QString sign READ sign WRITE setSign NOTIFY signChanged)
    Q_PROPERTY(QString state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString countryName READ countryName WRITE setCountryName NOTIFY countryNameChanged)
    Q_PROPERTY(QString countrySign READ countrySign WRITE setCountrySign NOTIFY countrySignChanged)
    Q_PROPERTY(QStringList countryColors READ countryColors WRITE setCountryColors NOTIFY countryColorsChanged)
    Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)
public:
    explicit CoverConnector(QObject *parent = nullptr);
    ~CoverConnector();

    enum Mode {
        Overview = 0,
        Item = 1,
        Country = 2,
        Wikipedia = 3
    };
    Q_ENUMS(Mode)

    QString country() const;
    QString name() const;
    QString type() const;
    QString sign() const;
    QString state() const;
    QString countryName() const;
    QString countrySign() const;
    QStringList countryColors() const;
    Mode mode() const;

    void setCountry(const QString &nCountry);
    void setName(const QString &nName);
    void setType(const QString &nType);
    void setSign(const QString &nSign);
    void setState(const QString &nState);
    void setCountryName(const QString &nCountryName);
    void setCountrySign(const QString &nCountrySign);
    void setCountryColors(const QStringList &nCountryColors);
    void setMode(Mode nMode);

signals:
    void countryChanged(const QString &country);
    void nameChanged(const QString &name);
    void typeChanged(const QString &type);
    void signChanged(const QString &sign);
    void stateChanged(const QString &state);
    void colorsChanged(const QStringList &colors);
    void countryNameChanged(const QString &countryName);
    void countrySignChanged(const QString &countrySign);
    void countryColorsChanged(const QStringList &countryColors);
    void modeChanged(Mode mode);

private:
    Q_DISABLE_COPY(CoverConnector)
    QString m_country;
    QString m_name;
    QString m_type;
    QString m_sign;
    QString m_state;
    QString m_countryName;
    QString m_countrySign;
    QStringList m_countryColors;
    Mode m_mode;
};

Q_DECLARE_METATYPE(CoverConnector::Mode)

#endif // COVERCONNECTOR_H
