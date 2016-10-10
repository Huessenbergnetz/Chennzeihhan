#!/bin/bash

echo "#ifndef DBSTRINGS_H
#define DBSTRINGS_H

class DBStrings
{
    Q_OBJECT" > dbstrings.h

sqlite3 -list carplates.sqlite "SELECT DISTINCT state FROM de WHERE state != '';" | sed 's/^\(.*\)/    QT_TRANSLATE_NOOP3("DBStrings", "\1", "Germany");/' >> dbstrings.h

sqlite3 -list carplates.sqlite "SELECT DISTINCT type FROM de WHERE type != '';" | sed 's/^\(.*\)/    QT_TRANSLATE_NOOP3("DBStrings", "\1", "Germany");/' >> dbstrings.h

sqlite3 -list carplates.sqlite "SELECT DISTINCT state FROM at WHERE state != '';" | sed 's/^\(.*\)/    QT_TRANSLATE_NOOP3("DBStrings", "\1", "Austria");/' >> dbstrings.h

sqlite3 -list carplates.sqlite "SELECT DISTINCT type FROM at WHERE type != '';" | sed 's/^\(.*\)/    QT_TRANSLATE_NOOP3("DBStrings", "\1", "Austria");/' >> dbstrings.h

sqlite3 -list carplates.sqlite "SELECT en FROM countries;" | sed 's/^\(.*\)/    QT_TRANSLATE_NOOP3("DBStrings", "\1", "Countries");/' >> dbstrings.h

echo "
};
#endif // DBSTRINGS_H" >> dbstrings.h 
