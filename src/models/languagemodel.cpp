#include "languagemodel.h"

const int LanguageModel::NameRole = Qt::UserRole + 1;
const int LanguageModel::ValueRole = Qt::UserRole + 2;

LanguageModel::LanguageModel(QObject *parent) :
    QAbstractListModel(parent)
{
    init();
}


QHash<int, QByteArray> LanguageModel::roleNames() const {
    QHash<int, QByteArray> roles = QAbstractItemModel::roleNames();
    roles.insert(NameRole, QByteArray("name"));
    roles.insert(ValueRole, QByteArray("value"));
    return roles;
}


int LanguageModel::rowCount(const QModelIndex &parent) const
{
    return m_langs.size();
}


QVariant LanguageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() > rowCount()-1)
        return QVariant();

    QString value = m_langs.at(index.row());
    switch(role) {
    case NameRole:
        return QVariant::fromValue(m_langCode[value]);
    case ValueRole:
        return QVariant::fromValue(value);
    default:
        return QVariant();
    }
}


QModelIndex LanguageModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent))
             return QModelIndex();

    return createIndex(row, column);
}


void LanguageModel::init()
{
    m_langs << "C" << "en_GB" << "de" << "it" << "nl_NL";
    m_langCode["C"] = tr("System default");
    m_langCode["en_GB"] = tr("English");
    m_langCode["de"] = tr("German");
    m_langCode["it"] = tr("Italian");
    m_langCode["nl_NL"] = tr("Dutch (Netherlands)");
}


QString LanguageModel::getLanguageName(const QString &langCode)
{
    return m_langCode[langCode];
}
