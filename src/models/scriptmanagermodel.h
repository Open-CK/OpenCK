/*
** scriptmanagermodel.h
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
** Created Date: 18-Jul-2017
*/

#ifndef SCRIPTMANAGERMODEL_H
#define SCRIPTMANAGERMODEL_H

#include <data/scriptmanagerdata.h>
#include <QAbstractItemModel>

namespace models
{
    class ScriptManagerModel : public QAbstractItemModel
    {
    public:
        enum ColumnType
        {
            COL_NAME,
            COL_TMPPATH,
            COL_STATUS,
            COL_PRIORITY
        };

        ScriptManagerModel(QObject* parent = Q_NULLPTR);
        ScriptManagerModel(const ScriptManagerModel&) = default;
        ScriptManagerModel& operator=(const ScriptManagerModel&) = default;
        ~ScriptManagerModel() = default;

        virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const override;
        virtual QModelIndex parent(const QModelIndex & child) const override;
        virtual int rowCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual int columnCount(const QModelIndex & parent = QModelIndex()) const override;
        virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const override;
        virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

        virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

        // Drag drop functionality.
        virtual Qt::ItemFlags flags(const QModelIndex & index) const override;
        virtual Qt::DropActions supportedDropActions() const override;
        //virtual QStringList mimeTypes() const override;
        virtual QMimeData* mimeData(const QModelIndexList& indices) const override;
        virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int col, const QModelIndex& parent) override;

        virtual bool insertRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;
        virtual bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    private:
        QVector<ScriptManagerData> scriptData;
        QVector<int> scriptDataIndices;

        QString statusCodeToString(int code) const;

        bool dropItem(const QMimeData* mimeData, int row, const QModelIndex& parent);
    };
}

#endif