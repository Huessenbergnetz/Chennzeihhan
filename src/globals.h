#ifndef GLOBALS_H
#define GLOBALS_H

#include <QStringList>
#include <QObject>

extern QStringList tables;

#define DB_PATH "/usr/share/harbour-chennzeihhan/data/carplates.sqlite"
#define VERSION_STRING "1.2.7"
#define VERSION 127
#define VER_MAJ 1
#define VER_MIN 2
#define VER_PAT 7
#define MIN_DB_VERSION 8

#define DATA_DIR "/.local/share/harbour-chennzeihhan"


class Chennzeihhan {
    Q_GADGET
public:
    enum Target {
        Code = 0,
        Name = 1,
        Both = 2
    };
    Q_ENUMS(Target)
};
Q_DECLARE_METATYPE(Chennzeihhan::Target)

#endif // GLOBALS_H
