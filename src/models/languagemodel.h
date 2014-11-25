#ifndef LANGUAGEMODEL_H
#define LANGUAGEMODEL_H

#include <QAbstractListModel>
#include <QHash>

class LanguageModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit LanguageModel(QObject *parent = 0);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QHash<int, QByteArray> roleNames() const;
    QModelIndex index(int row, int column = 0, const QModelIndex &parent = QModelIndex()) const;

    static const int ValueRole;
    static const int NameRole;

    QString getLanguageName(const QString &langCode);

signals:

public slots:

private:
    QList<QString> m_langs;
    QHash<QString, QString> m_langCode;
    void init();

};

#endif // LANGUAGEMODEL_H
