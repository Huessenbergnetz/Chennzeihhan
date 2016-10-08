#ifndef DEHELPER_H
#define DEHELPER_H

#include <QObject>

class DeHelper : public QObject
{
    Q_OBJECT
public:
    explicit DeHelper(QObject *parent = nullptr);

    QString getState(int state);
    QString getType(int type);
    bool isValid(const QString &assign, int closed);
};

#endif // DEHELPER_H
