#ifndef LANGUAGEMODELFILTER_H
#define LANGUAGEMODELFILTER_H

#include <QSortFilterProxyModel>
#include "languagemodel.h"

class LanguageModelFilter : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString search READ search WRITE setSearch NOTIFY searchChanged)
public:
    explicit LanguageModelFilter(QObject *parent = 0);

    QString search() const;

    Q_INVOKABLE QString getLanguageName(const QString &langCode);

signals:
    void searchChanged(const QString &nSearch);

public slots:
    void setSearch(const QString &nSearch);

private:
    QString m_search;
    LanguageModel m_sourceModel;
};

#endif // LANGUAGEMODELFILTER_H
