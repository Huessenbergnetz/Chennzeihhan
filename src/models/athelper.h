#ifndef ATHELPER_H
#define ATHELPER_H

#include <QObject>

class AtHelper : public QObject
{
    Q_OBJECT
public:
    explicit AtHelper(QObject *parent = 0);

    QString getState(int state);
    QString getType(int type);

signals:

public slots:

};

#endif // ATHELPER_H
