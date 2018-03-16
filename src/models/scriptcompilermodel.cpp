/*
** scriptcompilermodel.cpp
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

#include <models/scriptcompilermodel.h>
#include <data/scriptmanagerdata.h>
#include <QDebug>

namespace models
{
    ScriptCompilerModel::ScriptCompilerModel(QObject* parent)
        : QSortFilterProxyModel(parent)
    {
        //setDynamicSortFilter(true);
    }

    bool ScriptCompilerModel::lessThan(const QModelIndex& left, const QModelIndex& right) const
    {
        QVariant leftData = sourceModel()->data(left, Qt::UserRole);
        QVariant rightData = sourceModel()->data(right, Qt::UserRole);
        return leftData.toInt() < rightData.toInt();
    }

    bool ScriptCompilerModel::filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const
    {
        QModelIndex scriptStatusIndex = sourceModel()->index(sourceRow, 2);
        QModelIndex priorityIndex = sourceModel()->index(sourceRow, 3);
        return sourceModel()->data(scriptStatusIndex, Qt::UserRole).toInt() == static_cast<int>(ScriptStatus::COMPILE_WAIT) &&
               sourceModel()->data(priorityIndex, Qt::UserRole).toInt() >= 0;
    }

    void ScriptCompilerModel::setSourceModel(QAbstractItemModel* model)
    {
        QSortFilterProxyModel::setSourceModel(model);
        connect(model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(on_ScriptCompilerModel_dataChanged(const QModelIndex&, const QModelIndex&)));
    }

    void ScriptCompilerModel::on_ScriptCompilerModel_dataChanged(const QModelIndex& tl, const QModelIndex& br)
    {
        Q_UNUSED(tl);
        Q_UNUSED(br);
        invalidateFilter();
        invalidate();
    }

    Qt::ItemFlags ScriptCompilerModel::flags(const QModelIndex& index) const
    {
        Qt::ItemFlags flags = sourceModel()->flags(mapToSource(index));
        return flags;
    }

    bool ScriptCompilerModel::dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int col, const QModelIndex& parent)
    {
        if (row == -1 && col == -1)
            return sourceModel()->dropMimeData(data, action, -1, -1, mapToSource(parent));

        if (sortOrder() == Qt::DescendingOrder) {
            --row;
        }

        QModelIndex pIdx = index(row, col, parent);
        QModelIndex sIdx = mapToSource(pIdx);

        return this->sourceModel()->dropMimeData(data, action, sIdx.row(), sIdx.column(), sIdx.parent());
    }
}