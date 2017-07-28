/*
** formgroup.h
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
** Created Date: 28-Jul-2017
*/

#ifndef FORMGROUP_H
#define FORMGROUP_H

#include <QtEndian>

#include "form.h"

/**
 * The type of form group.
 * @brief The type of form group.
 */
enum class Type
{
    Top = 0,
    World_Children = 1,
    Interior_Cell_Block = 2,
    Interior_Cell_SubBlock = 3,
    Exterior_Cell_Block = 4,
    Exterior_Cell_SubBlock = 5,
    Cell_Children = 6,
    Topic_Children = 7,
    Cell_Persistent_Children = 8,
    Cell_Temporary_Children = 9,
    Cell_Visible_Distant_Children = 10,
    New = 11
};

/**
 * Class for groups inside forms.
 * @brief Class for groups inside forms.
 */
class FormGroup : public QObject
{
    Q_OBJECT

public:
    FormGroup(QDataStream *in, QByteArray *buffer);
    void load(QDataStream *in, int fileNumber);
    void loadTop(quint32 groupLabel, QDataStream *in, int fileNumber);

signals:
    void addForm(Form* form, int fileNumber);

private:
    /**
     * Size, in bytes, of the group (including 24-byte header).
     * @brief Size of the group.
     */
    quint32 groupSize = 0;
    /**
     * Label to identify group data.
     * @brief Group Label.
     */
    quint32 groupLabel = 0;
    /**
     * Enum to identify type of group, and therefore loading operation.
     * @brief Enum group type.
     */
    Type groupType = Type::New;
};

#endif // FORMGROUP_H
