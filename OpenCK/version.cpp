/*
** version.cpp
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

#include "version.h"

#include "QDebug"


//! @file version.cpp %OpenCK version number management

/**
 * The number of version parts.
 * @brief The number of version parts.
 */
int OpenCKVersion::numParts = 3;

/**
 * Constructs the version object based on a string.
 * @brief Constructs the version object.
 * @param ver The version in string format.
 */
OpenCKVersion::OpenCKVersion(const QString &ver)
    : rawVersion(ver), displayVersion(rawToDisplay(ver, true))
{

}

/**
 * Constructs the version object based on another object.
 * @brief Constructs the version object.
 * @param other The other object this object is based on.
 */
OpenCKVersion::OpenCKVersion(const OpenCKVersion &other)
    : rawVersion(other.rawVersion), displayVersion(other.displayVersion)
{

}

/**
 * Constructs the version object.
 * @brief Constructs the version object.
 */
OpenCKVersion::OpenCKVersion()
{

}
/**
 * Destructs the version object.
 * @brief Destructs the version object.
 */
OpenCKVersion::~OpenCKVersion()
{

}

/**
 * Gets a list of parts of the version.
 * @brief Gets a list of parts of the version.
 * @return A list of the parts of the version.
 */
QList<int> OpenCKVersion::parts() const
{
    return versionParts(rawVersion, numParts);
}

/**
 * Instance version of rawToMajMin(QString)
 * @brief Instance version of rawToMajMin(QString)
 * @return The version to major minor string format.
 */
QString OpenCKVersion::majMin() const
{
    return rawToMajMin(rawVersion);
}

/**
 * Instance version of hexVersion(QList<int>)
 * @brief Instance version of hexVersion(QList<int>)
 * @return The hexadecimal value of the version.
 */
int OpenCKVersion::hex() const
{
    return hexVersion(versionParts(rawVersion));
}

/**
 * Set the number of parts in the version string.
 * Max of 7 parts:
 *	0 = Major
 *	1 = Minor
 *	2 = Revision
 *	3 = Stage Code (Alpha, Beta, RC, Final)
 *	4 = Stage Version
 *	5 = Dev Code (dev, post)
 *	6 = Dev Version
 *
 * @note This sets OpenCKVersion::numParts (static) for *all* OpenCKVersion objects.
 * @brief Set the number of parts in the version string.
 * @param num The new number of parts.
 */
void OpenCKVersion::setNumParts(int num)
{
    if (num < 8 && num > 1) {
        numParts = num;
    }
}
/**
 * Integer representation of version string
 * represented in hex e.g. `"1.2.1" -> 0x010201 -> 66049`
 * @brief Return hex version of version string.
 * @param ver Version to convert
 * @return Hex version of version string.
 */
int OpenCKVersion::hexVersion(QString ver)
{
    return hexVersion(versionParts(ver));
}
/**
 * Integer representation of MajMinRev
 * represented in hex e.g. `"1.2.1" -> 0x010201 -> 66049`
 * @brief Return hex version of version string.
 * @param majMinRev MajMinRev integers to convert.
 * @return Hex version of Major/Minor/Revision.
 */
int OpenCKVersion::hexVersion(QList<int> majMinRev)
{
    // This can only work up to but not including 32-bit values
    // i.e. in this case a 4th value (n << 24) is possible
    // but I've decided to leave it as 3 parts only, to reflect
    // Qt's own QT_VERSION_CHECK macro.
    //
    // Granularity past MAJ.MIN.REV will require a OpenCKVersion object

    return (majMinRev[0] << 16) | (majMinRev[1] << 8) | (majMinRev[2]);
}

/**
 * Compare two versions strings beyond MajMinRev granularity.
 * @brief Compare two version strings.
 * @param ver1 Version one to compare.
 * @param ver2 Version two to compare.
 * @param parts Number of parts to compare.
 * @return `{-1, 0, 1}` meaning: `{ver1 < ver2, ver1 == ver2, ver1 > ver2}`
 */
int OpenCKVersion::compare(const QString &ver1, const QString &ver2, int parts)
{
    int oldNumParts = numParts;

    // Set granularity
    OpenCKVersion::setNumParts(parts);

    OpenCKVersion v1(ver1);
    OpenCKVersion v2(ver2);

    int ret = 0;

    if (v1 < v2) {
        ret = -1;
    } else if (v1 == v2) {
        ret = 0;
    } else {
        ret = 1;
    }
    // Reset granularity
    OpenCKVersion::setNumParts(oldNumParts);

    return ret;
}

/**
 * Compare two versions strings beyond MajMinRev granularity.
 * @brief Compare two version strings.
 * @param ver1 Version one to compare.
 * @param ver2 Version two to compare.
 * @return `{-1, 0, 1}` meaning: `{ver1 < ver2, ver1 == ver2, ver1 > ver2}`
 */
int OpenCKVersion::compare(const QString &ver1, const QString &ver2)
{
    return compare(ver1, ver2, numParts);
}

/**
 * Compare two versions strings beyond MajMinRev granularity.
 * @brief Compare two version strings.
 * @param ver1 Version one to compare.
 * @param ver2 Version two to compare.
 * @param parts Number of parts to compare.
 * @return true if `ver1 > ver2`
 */
bool OpenCKVersion::compareGreater(const QString &ver1, const QString &ver2, int parts)
{
    int oldNumParts = numParts;

    // Set granularity
    OpenCKVersion::setNumParts(parts);

    OpenCKVersion v1(ver1);
    OpenCKVersion v2(ver2);

    bool result = v1 > v2;

    // Reset granularity
    OpenCKVersion::setNumParts(oldNumParts);

    return result;
}

/**
 * Compare two versions strings beyond MajMinRev granularity.
 * @brief Compare two version strings.
 * @param ver1 Version one to compare.
 * @param ver2 Version two to compare.
 * @return true if `ver1 > ver2`
 */
bool OpenCKVersion::compareGreater(const QString &ver1, const QString &ver2)
{
    return compareGreater(ver1, ver2, numParts);
}

/**
 * Compare two versions strings beyond MajMinRev granularity.
 * @brief Compare two version strings.
 * @param ver1 Version one to compare.
 * @param ver2 Version two to compare.
 * @param parts Number of parts to compare.
 * @return true if `ver1 < ver2`
 */
bool OpenCKVersion::compareLess(const QString &ver1, const QString &ver2, int parts)
{
    int oldNumParts = numParts;

    // Set granularity
    OpenCKVersion::setNumParts(parts);

    OpenCKVersion v1(ver1);
    OpenCKVersion v2(ver2);

    bool result = v1 < v2;

    // Reset granularity
    OpenCKVersion::setNumParts(oldNumParts);

    return result;
}

/**
 * Compare two versions strings beyond MajMinRev granularity.
 * @brief Compare two version strings.
 * @param ver1 Version one to compare.
 * @param ver2 Version two to compare.
 * @return true if `ver1 < ver2`
 */
bool OpenCKVersion::compareLess(const QString &ver1, const QString &ver2)
{
    return compareLess(ver1, ver2, numParts);
}

/**
 * Format raw version string into a formatted display string.
 * @brief Format version string for display.
 * @param ver Version string to format.
 * @param showStage Whether to show release stage e.g. "1.2.0 Alpha 1"
 * @param showDev Whether to show dev release e.g. "1.2.0 Alpha 1 Dev 1"
 * @return The formatted string.
 */
QString OpenCKVersion::rawToDisplay(const QString &ver, bool showStage = false, bool showDev = false)
{
    // Explicitly call all parts (i.e. 7)
    QList<int> verList = versionParts(ver, 7);

    if (verList.isEmpty()) {
        return QString();
    }
    QString verString = QString("%1.%2.%3").arg(verList[0]).arg(verList[1]).arg(verList[2]);
    QString stage, dev;

    QList<QString> stages { "Pre-Alpha", "Alpha", "Beta", "RC", "" };
    QList<QString> devs { "Dev", "Post" };

    if (showStage) {
        stage = stages.value(verList.value(3, 4), "");
        int stageVer = verList.value(4, -1);

        if (!stage.isEmpty() && stageVer > 0) {
            // Append Stage
            verString = QString("%1 %2 %3").arg(verString).arg(stage).arg(stageVer);

            if (showDev) {
                dev = devs.value(verList.value(5, -1), "");
                int devVer = verList.value(6, -1);

                if (!dev.isEmpty() && devVer > 0) {
                    // Append Dev
                    verString = QString("%1 %2 %3").arg(verString).arg(dev).arg(devVer);
                }
            }
        }
    }
    return verString;
}

/**
 * Get version string for MAJ.MIN format.
 * @brief Get version string for MAJ.MIN format.
 * @param ver Version string to format.
 * @return Formatted string.
 */
QString OpenCKVersion::rawToMajMin(const QString &ver)
{
    QList<int> parts = versionParts(ver, 2);

    return QString("%1.%2").arg(parts[0]).arg(parts[1]);
}


/**
 * Gets version parts for any version string.
 * @brief Get parts of version string.
 * @param ver Version string to get parts of.
 * @param parts (7)	Number of parts to return
 * @return	Version parts of length `parts`
 */
QList<int> OpenCKVersion::versionParts(const QString &ver, int parts = 7)
{
    QList<int> verList;

    if (formatVersion(ver, verList, parts)) {
        return verList;
    }
    return QList<int>();
}


/**
 *  Checks if a version string is valid.
 *	Some examples of version strings:
 *
 *	Valid
 *		"1.0.0",
 *		"1.0.1a1",
 *		"1.0.2b1.dev1",
 *		"1.1.dev1",
 *		"1.1.12a1",
 *		"1.1.12.post1"
 *
 *	Invalid, but compensated for
 *		"1.1.3.a1.dev2",
 *		"1.2.0a.dev1",
 *		"1.3.0a",
 *		"1.4.0rc"
 * @brief Checks if a version string is valid.
 * @param ver Version string to check.
 * @param verNums Version string encoded as a list of integers
 * @param parts Number of parts to return
 * @return true if valid string, false if invalid string
 */
bool OpenCKVersion::formatVersion(const QString &ver, QList<int> &verNums, int parts)
{
    QString v = ver;

    if (ver.isEmpty()) {
        v = "0.0.0";
    }

    if (parts > 7 || parts < 2) {
        parts = 3;
    }

    QStringList verParts = v.split(".");
    QList<int> rawVersionNums;

    // The version string must at least have one period e.g. "1.2"
    if (verParts.count() < 2)
        verParts = QStringList({ "0", "0", "0" });

    QString major = verParts[0];
    QString minor = verParts[1];
    // Deal with missing .0, e.g. "1.2" instead of "1.2.0"
    QString rev = verParts.value(2, "0");

    bool majIsNum;
    bool minIsNum;

    int majNum = major.toInt(&majIsNum);
    int minNum = minor.toInt(&minIsNum);

    if (!majIsNum || !minIsNum) {
        return false;
    }

    // Combine Version parts
    rawVersionNums.append({majNum, minNum});

    // Confirm fourth part begins with "dev" or "post"
    // and not "a", "b", or "rc" (an invalid naming scheme)
    // dev = 0, post = 1
    QString dev = verParts.value(3, "");
    QString devVer = "-1";
    int devCode = -1;

    if (dev.startsWith("a") || dev.startsWith("b") || dev.startsWith("rc" )) {
        // Invalid version format
        //	Valid: 1.2.0a1.dev1
        //	Invalid: 1.2.0.a1.dev1
        // Remove dot here to compensate
        rev += dev;
        // Reassign dev to 4th value
        dev = verParts.value(4, "");
    }

    if ( dev.startsWith("dev") || dev.startsWith("post")) {
        // Normal developmental suffix
        if ( dev.startsWith("dev")) {
            devCode = 0;
            devVer = dev.mid(3);
        } else {
            devCode = 1;
            devVer = dev.mid(4);
        }
    }

    int devNum = devVer.toInt();

    // Stage Code
    //	0 = dev (pre-alpha)
    //	1 = alpha
    //	2 = beta
    //	3 = rc
    //	4 = final
    int stageCode = 4;
    QString stageVer = "-1";

    // Check if Revision has an a, b, rc appended
    bool isFinal;
    rev.toInt(&isFinal);
    if (!isFinal && rev >= 0) {
        // Pre-Release Build
        QStringList revParts; // "0a1" -> ("0", "1")
        QString revPart;      // "0a1" -> "0"
        QString stagePart;    // "0a1" -> "a"
        QString stageVerPart; // "0a1" -> "1"

        if (rev.startsWith("dev")) {
            // Pre-Alpha Dev
            //	e.g. 1.2.dev1, not 1.2.0dev1, not 1.2.0.dev1
            stagePart = "dev";
            stageVer = rev.mid(3);
            stageCode = 0;
            // Unset rev
            rev = "0";
        } else if (rev.length() > 1) {
            // Pre-Release
            if (rev.contains("a")) {
                stagePart = "a";
                stageCode = 1;
            } else if (rev.contains("b")) {
                stagePart = "b";
                stageCode = 2;
            } else if (rev.contains("rc")) {
                stagePart = "rc";
                stageCode = 3;
            }

            // Splitting at stagePart gives you a list with the rev and stageVer
            //	e.g. "0a1" becomes ("0", "1")
            revParts = rev.split(stagePart, QString::SkipEmptyParts);
            // This is the revision number without e.g. "a1" appended
            revPart = revParts.value(0, "0");
            // This is the version of the Alpha/Beta/RC
            stageVerPart = revParts.value(1, "1");

            // Set Revision and Stage Version
            rev = revPart;
            stageVer = stageVerPart;
        }
    }

    int stageNum = stageVer.toInt();

    // Append Revision part
    bool revIsNum;
    int revNum = rev.toInt(&revIsNum);

    if (!revIsNum) {
        return false;
    }

    rawVersionNums.append({revNum, stageCode, stageNum, devCode, devNum});
    verNums = rawVersionNums.mid(0, parts);

    return true;
}


// Using std::list<int> here removes the need for the for loop as it
// has its own operator overloads already. Yet best not rely on it.

bool OpenCKVersion::operator<(const OpenCKVersion &other) const
{
    QList<int> verParts1, verParts2;

    verParts1 = versionParts(rawVersion, numParts);
    verParts2 = versionParts(other.rawVersion, numParts);

    for (int i = 0; i < numParts; i++) {
        if (verParts1[i] == verParts2[i]) {
            continue;
        }
        return verParts1[i] < verParts2[i];
    }
    return false;
}

bool OpenCKVersion::operator<=(const OpenCKVersion &other) const
{
    QList<int> verParts1, verParts2;

    verParts1 = versionParts(rawVersion, numParts);
    verParts2 = versionParts(other.rawVersion, numParts);

    for (int i = 0; i < numParts; i++) {
        if (verParts1[i] == verParts2[i]) {
            continue;
        }
        return verParts1[i] < verParts2[i];
    }
    return true;
}

bool OpenCKVersion::operator==(const OpenCKVersion &other) const
{
    QList<int> verParts1, verParts2;

    verParts1 = versionParts(rawVersion, numParts);
    verParts2 = versionParts(other.rawVersion, numParts);

    for (int i = 0; i < numParts; i++) {
        if (verParts1[i] != verParts2[i]) {
            return false;
        }
    }
    return true;
}

bool OpenCKVersion::operator!=(const OpenCKVersion &other) const
{
    QList<int> verParts1, verParts2;

    verParts1 = versionParts(rawVersion, numParts);
    verParts2 = versionParts(other.rawVersion, numParts);

    for (int i = 0; i < numParts; i++) {
        if (verParts1[i] != verParts2[i]) {
            return true;
        }
    }
    return false;
}

bool OpenCKVersion::operator>(const OpenCKVersion &other) const
{
    QList<int> verParts1, verParts2;

    verParts1 = versionParts(rawVersion, numParts);
    verParts2 = versionParts(other.rawVersion, numParts);

    for (int i = 0; i < numParts; i++) {
        if (verParts1[i] == verParts2[i]) {
            continue;
        }
        return verParts1[i] > verParts2[i];
    }
    return false;
}

bool OpenCKVersion::operator>=(const OpenCKVersion &other) const
{
    QList<int> verParts1, verParts2;

    verParts1 = versionParts(rawVersion, numParts);
    verParts2 = versionParts(other.rawVersion, numParts);

    for (int i = 0; i < numParts; i++) {
        if (verParts1[i] == verParts2[i]) {
            continue;
        }
        return verParts1[i] > verParts2[i];
    }
    return true;
}

bool OpenCKVersion::operator<(const QString &other) const
{
    return operator<(OpenCKVersion(other));
}

bool OpenCKVersion::operator<=(const QString &other) const
{
    return operator<=(OpenCKVersion(other));
}

bool OpenCKVersion::operator==(const QString &other) const
{
    return operator==(OpenCKVersion(other));
}

bool OpenCKVersion::operator!=(const QString &other) const
{
    return operator!=(OpenCKVersion(other));
}

bool OpenCKVersion::operator>(const QString &other) const
{
    return operator>(OpenCKVersion(other));
}

bool OpenCKVersion::operator>=(const QString &other) const
{
    return operator>=(OpenCKVersion(other));
}

/**
 * QDebug operator for OpenCKVersion.
 *
 * Prints rawVersion, displayVersion, parts()
 *		e.g. "1.2.0a1.dev19" "1.2.0 Alpha 1" (1, 2, 0, 1, 1, 0, 19)
 * @brief QDebug operator for OpenCKVersion.
 */
QDebug operator<<(QDebug dbg, const OpenCKVersion &ver)
{
    ver.setNumParts(7);
    return dbg.space() << ver.rawVersion << ver.displayVersion << ver.parts();
}
