#ifndef EXTENDEDITEM_H
#define EXTENDEDITEM_H

#include <QObject>
#include "item.h"

class SimpleItemModel;

/*!
 * \brief The ExtendedItem class.
 */
class ExtendedItem : public Item
{
    Q_OBJECT
    Q_PROPERTY(SimpleItemModel *antecessors READ antecessors CONSTANT)
    Q_PROPERTY(QString successor READ successor NOTIFY successorChanged)
    Q_PROPERTY(uint successorId READ successorId NOTIFY successorIdChanged)
    Q_PROPERTY(QString tpo READ tpo NOTIFY tpoChanged)
    Q_PROPERTY(uint tpoId READ tpoId NOTIFY tpoIdChanged)
    Q_PROPERTY(QString optionalSigns READ optionalSigns NOTIFY optionalSignsChanged)
public:
    explicit ExtendedItem(QObject *parent = nullptr);
    ~ExtendedItem();

    SimpleItemModel *antecessors() const;
    QString successor() const;
    uint successorId() const;
    QString tpo() const;
    uint tpoId() const;
    QString optionalSigns() const;

signals:
    void antecessorsChanged(SimpleItemModel *antecessors);
    void successorChanged(const QString &successor);
    void successorIdChanged(uint successorId);
    void tpoChanged(const QString &tpo);
    void tpoIdChanged(uint tpoId);
    void optionalSignsChanged(const QString &optionalSigns);

protected:
    void setSuccessor(const QString &nSuccessor);
    void setSuccessorId(uint nSuccessorId);
    void setTpo(const QString &nTpo);
    void setTpoId(uint nTpoId);
    void setOptionalSigns(const QString &nOptionalSigns);

    void clear();

private:
    Q_DISABLE_COPY(ExtendedItem)
    SimpleItemModel *m_antecessors;
    QString m_successor;
    uint m_successorId;
    QString m_tpo;
    uint m_tpoId;
    QString m_optionalSigns;
};

#endif // EXTENDEDITEM_H
