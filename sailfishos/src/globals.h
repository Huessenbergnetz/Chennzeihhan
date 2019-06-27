/*
    Chennzeihhan - Vehicle Registration Code Database for SailfishOS
    Copyright (C) 2014-2019 Hüssenbergnetz/Matthias Fehring

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef GLOBALS_H
#define GLOBALS_H

#include <QStringList>
#include <QObject>

#define VERSION_STRING "1.3.0"
#define VERSION 130
#define VER_MAJ 1
#define VER_MIN 3
#define VER_PAT 0
#define MIN_DB_VERSION 16

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
