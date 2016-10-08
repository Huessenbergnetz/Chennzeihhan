#ifndef ATHELPER_H
#define ATHELPER_H

#include <QObject>

class AtHelper : public QObject
{
    Q_OBJECT
public:
    explicit AtHelper(QObject *parent = nullptr);

    QString getState(int state);
    QString getType(int type);
};

#endif // ATHELPER_H
