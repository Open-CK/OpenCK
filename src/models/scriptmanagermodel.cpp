/*
** scriptmanagermodel.cpp
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

#include <models/scriptmanagermodel.h>
#include <QDebug>
#include <QMimeData>
#include <QDataStream>

namespace models
{
    ScriptManagerModel::ScriptManagerModel(QObject* parent)
        : QAbstractItemModel(parent)
    {
    }

    QModelIndex ScriptManagerModel::index(int row, int column, const QModelIndex& parent) const
    {
        return createIndex(row, column, nullptr);
    }

    QModelIndex ScriptManagerModel::parent(const QModelIndex& child) const
    {
        return {};
    }

    int ScriptManagerModel::rowCount(const QModelIndex& parent) const
    {
        return scriptData.count();
    }

    int ScriptManagerModel::columnCount(const QModelIndex& parent) const
    {
        return 4;
    }

    QVariant ScriptManagerModel::data(const QModelIndex& index, int role) const
    {
        if (!index.isValid())
            return {};

        if (index.row() >= scriptData.size())
            return {};

        auto& scData = scriptData[index.row()];
        if (role == Qt::DisplayRole) {
            switch (index.column()) {
            case COL_NAME: return scData.name;
            case COL_TMPPATH: return scData.tmpPath;
            case COL_STATUS: return statusCodeToString(static_cast<int>(scData.status));
            case COL_PRIORITY: return QString::number(scData.priority);
            default: return {};
            }
        }
        else if (role == Qt::UserRole) {
            switch (index.column()) {
            case COL_NAME: return scData.name;
            case COL_TMPPATH: return scData.tmpPath;
            case COL_STATUS: return static_cast<int>(scData.status);
            case COL_PRIORITY: return scData.priority;
            default: return {};
            }
        }

        return {};
    }
    
    bool ScriptManagerModel::setData(const QModelIndex &index, const QVariant &value, int role)
    {
        if (index.isValid()) {

            auto& scData = scriptData[index.row()];
            if (role == Qt::DisplayRole) {
                switch (index.column()) {
                case COL_NAME: scData.name = value.toString(); break;
                case COL_STATUS: scData.status = static_cast<ScriptStatus>(value.toInt()); break;
                default: return false;
                }
            }
            else if (role == Qt::UserRole) {
                switch (index.column()) {
                case COL_NAME: scData.name = value.toString(); break;
                case COL_TMPPATH: scData.tmpPath = value.toString(); break;
                case COL_STATUS: 
                {
                    auto status = static_cast<ScriptStatus>(value.toInt()); 
                    
                    if (scData.status != ScriptStatus::COMPILE_WAIT && status == ScriptStatus::COMPILE_WAIT)
                    {
                        // Add to compile queue.
                        int p = scriptDataIndices.size();
                        scriptDataIndices.push_back(p);
                        scData.priority = p;
                    }
                    else if(status != ScriptStatus::COMPILE_WAIT)
                    {
                        scData.priority = -1;
                    }

                    scData.status = status;

                    break;
                }
                case COL_PRIORITY: scData.priority = value.toInt(); break;
                default: return false;
                }
            }

            QModelIndex tl = createIndex(index.row(), COL_NAME);
            QModelIndex br = createIndex(index.row(), COL_PRIORITY);
            emit dataChanged(tl, br);
            return true;
        }

        return false;
    }

    QVariant ScriptManagerModel::headerData(int section, Qt::Orientation orientation, int role) const
    {
        if (role == Qt::DisplayRole) {
            switch (section) {
            case COL_NAME: return "Name";
            case COL_TMPPATH: return "Temp Path";
            case COL_STATUS: return "Status";
            case COL_PRIORITY: return "Priority";
            }
        }
        return {};
    }

    Qt::ItemFlags ScriptManagerModel::flags(const QModelIndex& index) const
    {
        Qt::ItemFlags result = QAbstractItemModel::flags(index);

        if (index.model() < 0) {
            return Qt::ItemIsEnabled;
        }

        return result | Qt::ItemIsDragEnabled | Qt::ItemIsEnabled | Qt::ItemIsDropEnabled;
    }

    Qt::DropActions ScriptManagerModel::supportedDropActions() const
    {
        return Qt::MoveAction;
    }

    QMimeData* ScriptManagerModel::mimeData(const QModelIndexList& indices) const
    {
        QMimeData* mimeData = QAbstractItemModel::mimeData(indices);
        mimeData->setData("text/plain", "item");
        return mimeData;
    }

    bool ScriptManagerModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int col, const QModelIndex& parent)
    {
        if (action == Qt::IgnoreAction)
            return true;

        if (data->hasText()) {
            return dropItem(data, row, parent);
        }

        return false;
    }

    bool ScriptManagerModel::dropItem(const QMimeData* mimeData, int row, const QModelIndex& parent)
    {
        try {

            QByteArray encoded = mimeData->data("application/x-qabstractitemmodeldatalist");
            QDataStream stream(&encoded, QIODevice::ReadOnly);

            // Decode information of the dropped item.
            std::vector<int> srcRows;
            while (!stream.atEnd()) {
                int srcRow, col;
                QMap<int, QVariant> roleMap;
                stream >> srcRow >> col >> roleMap;
                if (col == 0) {
                    srcRows.push_back(srcRow);
                }
            }

            // row contains the position of where the drop was complete.
            //qDebug() << "Drop row: " << row << " from row: " << srcRows[0];

            if (row == -1) {
                row = parent.row();
            }

            if (row < 0 || row >= scriptData.size())
                return false;

            //auto sr = index(srcRows[0], 3);
            //auto dr = index(row, 3);
            auto& sr = scriptData[srcRows[0]];
            auto& dr = scriptData[row];

            // pull indices and sort to temporary.
            // TODO: Cache indices instead.
            QVector<ScriptManagerData*> indices;
            for (auto& item : scriptData) {
                if (item.status == ScriptStatus::COMPILE_WAIT) {
                    indices.push_back(&item);
                }
            }

            // We need to check if we are going below or above.
            if (sr.priority < dr.priority) {

                qSort(indices.begin(), indices.end(), [](ScriptManagerData* lhs, ScriptManagerData* rhs) {
                    return lhs->priority > rhs->priority;
                });
                // Set our source to the drop priority.
                sr.priority = dr.priority;

                int nextIndex = sr.priority - 1;
                for (auto* item : indices) {
                    if (item->priority <= sr.priority && (item != &sr)) {
                        item->priority = nextIndex;
                        nextIndex--;
                    }
                }
            }
            else
            {
                qSort(indices.begin(), indices.end(), [](ScriptManagerData* lhs, ScriptManagerData* rhs) {
                    return lhs->priority < rhs->priority;
                });
                // Set our source to the drop priority.
                sr.priority = dr.priority;

                // Iterate items to recalculate priority.
                int nextIndex = sr.priority + 1;
                for (auto* item : indices) {
                    if (item->priority >= sr.priority && (item != &sr)) {
                        
                        item->priority = nextIndex;
                        nextIndex++;
                    }
                }
            }

            QModelIndex top = createIndex(scriptData.size() - 1, 0);
            QModelIndex bottom = createIndex(scriptData.size() - 1, 3);
            emit dataChanged(top, bottom);
        }
        catch (const std::exception& e)
        {
            return false;
        }
        return false;
    }

    bool ScriptManagerModel::insertRows(int row, int count, const QModelIndex& parent)
    {
        beginInsertRows({}, row, row + (count - 1));
        scriptData.insert(row, count, {});
        endInsertRows();

        //updateScriptDataIndices();

        return true;
    }

    bool ScriptManagerModel::removeRows(int row, int count, const QModelIndex& parent)
    {
        beginRemoveRows({}, row, row + (count - 1));
        scriptData.remove(row, count);
        endRemoveRows();

        //updateScriptDataIndices();

        return true;
    }

    QString ScriptManagerModel::statusCodeToString(int code) const
    {
        ScriptStatus status = static_cast<ScriptStatus>(code);
        switch (status) {
        case ScriptStatus::NONE: return "";
        case ScriptStatus::DIRTY: return "Dirty";
        case ScriptStatus::COMPILE_WAIT: return "Compilation Queued";
        case ScriptStatus::COMPILE_SUCCESS: return "Compile Success";
        case ScriptStatus::COMPILE_FAIL: return "Compile Fail";
        default: return "";
        }
    }
}
