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


static const QHash<QString, QString> migrateTo1_2 = {
        { "Export Settings/export_culling", "Export Settings/Export Culling" },
        { "auto sanitize", "File/Auto Sanitize" },
        { "last load", "File/Last Load" }, { "last save", "File/Last Save" },
        { "fsengine/archives", "FSEngine/Archives" },
        { "enable animations", "GLView/Enable Animations" }, { "LOD/LOD Level", "GLView/LOD Level" },
        { "loop animation", "GLView/Loop Animation" }, { "perspective", "GLView/Perspective" },
        { "play animation", "GLView/Play Animation" }, { "switch animation", "GLView/Switch Animation" },
        { "view action", "GLView/View Action" },
        { "JPEG/Quality", "JPEG/Quality" },
        { "Render Settings/Anti Aliasing", "Render Settings/Anti Aliasing" }, { "Render Settings/Background", "Render Settings/Background" },
        { "Render Settings/Cull Expression", "Render Settings/Cull Expression" }, { "Render Settings/Cull Nodes By Name", "Render Settings/Cull Nodes By Name" },
        { "Render Settings/Cull Non Textured", "Render Settings/Cull Non Textured" }, { "Render Settings/Draw Axes", "Render Settings/Draw Axes" },
        { "Render Settings/Draw Collision Geometry", "Render Settings/Draw Collision Geometry" }, { "Render Settings/Draw Constraints", "Render Settings/Draw Constraints" },
        { "Render Settings/Draw Furniture Markers", "Render Settings/Draw Furniture Markers" }, { "Render Settings/Draw Nodes", "Render Settings/Draw Nodes" },
        { "Render Settings/Enable Shaders", "Render Settings/Enable Shaders" }, { "Render Settings/Foreground", "Render Settings/Foreground" },
        { "Render Settings/Highlight", "Render Settings/Highlight" },
        { "Render Settings/Show Hidden Objects", "Render Settings/Show Hidden Objects" }, { "Render Settings/Show Stats", "Render Settings/Show Stats" },
        { "Render Settings/Texture Alternatives", "Render Settings/Texture Alternatives" }, { "Render Settings/Texture Folders", "Render Settings/Texture Folders" },
        { "Render Settings/Texturing", "Render Settings/Texturing" }, { "Render Settings/Up Axis", "Render Settings/Up Axis" },
        { "Settings/Language", "Settings/Language" }, { "Settings/Startup Version", "Settings/Startup Version" },
        { "hide condition zero", "UI/Hide Mismatched Rows" }, { "realtime condition updating", "UI/Realtime Condition Updating" },
        { "XML Checker/Directory", "XML Checker/Directory" }, { "XML Checker/Recursive", "XML Checker/Recursive" },
        { "XML Checker/Threads", "XML Checker/Threads" }, { "XML Checker/check kf", "XML Checker/Check KF" },
        { "XML Checker/check kfm", "XML Checker/Check KFM" }, { "XML Checker/check nif", "XML Checker/Check NIF" },
        { "XML Checker/report errors only", "XML Checker/Report Errors Only" },
        { "import-export/3ds/File Name", "Import-Export/3DS/File Name" }, { "import-export/obj/File Name", "Import-Export/OBJ/File Name" },
        { "spells/Block/Remove By Id/match expression", "Spells/Block/Remove By Id/Match Expression" },
        { "last texture path", "Spells/Texture/Choose/Last Texture Path" },
        { "spells/Texture/Export Template/Antialias", "Spells/Texture/Export Template/Antialias" },
        { "spells/Texture/Export Template/File Name", "Spells/Texture/Export Template/File Name" },
        { "spells/Texture/Export Template/Image Size", "Spells/Texture/Export Template/Image Size" },
        { "spells/Texture/Export Template/Wire Color", "Spells/Texture/Export Template/Wire Color" },
        { "spells/Texture/Export Template/Wrap Mode", "Spells/Texture/Export Template/Wrap Mode" },
        { "version", "Version" }
};

static const QHash<QString, QString> migrateTo2_0 = {
        { "Export Settings/Export Culling", "Export Settings/Export Culling" },
        { "File/Recent File List", "File/Recent File List" },
        { "File/Auto Sanitize", "File/Auto Sanitize" },
        { "File/Last Load", "File/Last Load" }, { "File/Last Save", "File/Last Save" },
        { "FSEngine/Archives", "FSEngine/Archives" },
        { "Render Settings/Anti Aliasing", "Render Settings/Anti Aliasing" },
        { "Render Settings/Texturing", "Render Settings/Texturing" },
        { "Render Settings/Enable Shaders", "Render Settings/Enable Shaders" },
        { "Render Settings/Background", "Render Settings/Background" },
        { "Render Settings/Foreground", "Render Settings/Foreground" },
        { "Render Settings/Highlight", "Render Settings/Highlight" },
        { "Render Settings/Texture Alternatives", "Render Settings/Texture Alternatives" },
        { "Render Settings/Texture Folders", "Render Settings/Texture Folders" },
        { "Render Settings/Up Axis", "Render Settings/Up Axis" },
        { "Settings/Language", "Settings/Language" }, { "Settings/Startup Version", "Settings/Startup Version" },
};


#endif
