#ifndef DEHELPER_H
#define DEHELPER_H

#include <QObject>

class DeHelper : public QObject
{
    Q_OBJECT
public:
    explicit DeHelper(QObject *parent = 0);

    QString getState(int state);
    QString getType(int type);
    bool isValid(const QString &assign, int closed);

signals:

public slots:

};

#endif // DEHELPER_H
