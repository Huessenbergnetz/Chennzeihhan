#include "languagemodelfilter.h"

LanguageModelFilter::LanguageModelFilter(QObject *parent) :
    QSortFilterProxyModel(parent)
{
    this->setSourceModel(&m_sourceModel);
    this->setFilterRole(LanguageModel::NameRole);
    this->setFilterCaseSensitivity(Qt::CaseInsensitive);
    this->setSortLocaleAware(true);
    this->setSortRole(LanguageModel::NameRole);
    this->sort(0);
}


QString LanguageModelFilter::search() const
{
    return m_search;
}


void LanguageModelFilter::setSearch(const QString &nSearch)
{
    if (nSearch != m_search) {
        m_search = nSearch;
        this->setFilterFixedString(search());
        emit searchChanged(search());
    }
}


QString LanguageModelFilter::getLanguageName(const QString &langCode)
{
    return m_sourceModel.getLanguageName(langCode);
}
