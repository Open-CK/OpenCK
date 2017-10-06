/*
** version.h
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 19-Jul-2017
*/

//!@file version.h Header for version control.

/**
  * Credit to jonwd7 and nifskope for large parts of the file.
  */
#ifndef VERSION_H
#define VERSION_H

#include <QHash>
#include <QList>
#include <QString>
#include <QStringList>

// Forward declarations
class QDebug;


//! Define current OpenCK version as hex int
#define OPENCK_VERSION_HEX OpenCKVersion::hexVersion(OPENCK_VERSION)

/**
 * Encapsulates application version strings into comparable objects and provides static convenience
 * functions for raw strings.
 *
 * For comparison purposes, such as for migrating QSettings between versions,
 * or removing deprecated QSettings.
 *
 * For formatting purposes, such as display strings for window titles.
 * @brief The version class controls the versioning of OpenCK.
 */
class OpenCKVersion final
{

public:
    OpenCKVersion(const QString &ver);
    OpenCKVersion(const OpenCKVersion &other);
    ~OpenCKVersion();

    /**
     * Raw string as stored in VERSION file or registry.
     * @brief Raw version string.
     */
    const QString rawVersion;
    /**
     * Display string formatted for readability.
     * @brief Formatted version string.
     */
    const QString displayVersion;

    QList<int> parts() const;
    QString majMin() const;
    int hex() const;


    static void setNumParts(int num);

    static int hexVersion(const QString ver);
    static int hexVersion(const QList<int> majMinRev);

    static int compare(const QString &ver1, const QString &ver2, int parts);
    static int compare(const QString &ver1, const QString &ver2);

    static bool compareGreater(const QString &ver1, const QString &ver2, int parts);
    static bool compareGreater(const QString &ver1, const QString &ver2);

    static bool compareLess(const QString &ver1, const QString &ver2, int parts);
    static bool compareLess(const QString &ver1, const QString &ver2);

    static QString rawToDisplay(const QString &ver, bool showStage = false, bool showDev = false);
    static QString rawToMajMin(const QString &ver);

    static QList<int> versionParts(const QString &ver, int parts = 7);

    static bool formatVersion(const QString &ver, QList<int> &verNums, int parts = 3);

    // Compare two OpenCKVersions
    bool operator<(const OpenCKVersion &other) const;
    bool operator<=(const OpenCKVersion &other) const;
    bool operator==(const OpenCKVersion &other) const;
    bool operator!=(const OpenCKVersion &other) const;
    bool operator>(const OpenCKVersion &other) const;
    bool operator>=(const OpenCKVersion &other) const;

    // Compare a OpenCKVersion to a QString
    bool operator<(const QString &other) const;
    bool operator<=(const QString &other) const;
    bool operator==(const QString &other) const;
    bool operator!=(const QString &other) const;
    bool operator>(const QString &other) const;
    bool operator>=(const QString &other) const;

protected:
    OpenCKVersion();

    /**
     * Number of parts for version strings.
     * @brief Number of parts for version strings.
     * @note Static, so global across all instances.
     */
    static int numParts;
};

QDebug operator<<(QDebug dbg, const OpenCKVersion &ver);

#endif
