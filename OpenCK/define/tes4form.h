/*
** tes4record.h
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
** Created Date: 10-Jul-2017
*/

//!@file tes4form.h Header for the TES4 record class.

#ifndef TES4FORM_H
#define TES4FORM_H

#include <QString>
#include <QMap>
#include <QVector>

#include "form.h"

namespace Define
{
    class TES4Form;
}

/**
 * The class for the TES4 header in .esp and .esm files.
 * @brief The class for the TES4 header.
 */
class TES4Form : public Form
{
public:
    TES4Form();
    ~TES4Form();
    void load(QDataStream* in, int fileNumber);

    float getTES4Version() const;
    quint32 getNumRecords() const;
    quint32 getNextID() const;
    QString getAuthor() const;
    QString getDesc() const;
    QMap<QString, quint64> getMasters() const;
    QVector<quint32> getOverrides() const;
    quint32 getIntv() const;
    quint32 getIncc() const;

    void setTES4Version(const float in);
    void setNumRecords(const quint32 in);
    void setNextID(const quint32 in);
    void setAuthor(const QString in);
    void setDesc(const QString in);
    void setMasters(const QMap<QString, quint64> in);
    void setOverrides(const QVector<quint32> in);
    void setIntv(const quint32 in);
    void setIncc(const quint32 in);

private:
    /**
     * The version of the .esm/.esp file parsed.
     * @brief The version of the file parsed.
     */
    float version;
    /**
     * The amount of records in the parsed file.
     * @brief The amount of records.
     */
    qint32 records;
    /**
     * The next available object id.
     * @brief The next object id.
     */
    quint32 nextID;
    /**
     * The author of the file. Note: Optional
     * @brief The author of the file.
     */
    QString author;
    /**
     * The description of the file. Note: Optional
     * @brief The description of the file.
     */
    QString desc;
    /**
     * The masterfiles of this file's names and sizes. Note: In TES4/TES5, size is constant 0.
     * @brief The masterfiles of this file's names and sizes.
     */
    QMap<QString, quint64> masters;
    /**
     * The IDs of any overridden forms of a master file. Only appears in ESM-flagged files.
     * @brief Dynamic array of overriden FormIDs.
     */
    QVector<quint32> overrides;
    /**
     * An unknown value, likely internal version.
     * @brief Unknown.
     */
    quint32 intv;
    /**
     * An unknown value. Note: Optional
     * @brief Unknown.
     */
    quint32 incc;
};

#endif // TES4FORM_H
