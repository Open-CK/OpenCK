/*
** scriptcompilermodel.h
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

#ifndef SCRIPTCOMPILERMODEL_H
#define SCRIPTCOMPILERMODEL_H

#include <QSortFilterProxyModel>
#include <QVector>

namespace models
{
    class ScriptCompilerModel : public QSortFilterProxyModel
    {
        Q_OBJECT
    public:
        ScriptCompilerModel(QObject* parent = Q_NULLPTR);
        ScriptCompilerModel(const ScriptCompilerModel&) = default;
        ScriptCompilerModel& operator=(const ScriptCompilerModel&) = default;
        ~ScriptCompilerModel() = default;

        virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const override;
        virtual bool filterAcceptsRow(int sourceRow, const QModelIndex& sourceParent) const override;

        virtual void setSourceModel(QAbstractItemModel* model) override;

        virtual Qt::ItemFlags flags(const QModelIndex& index) const override;
        virtual bool dropMimeData(const QMimeData* data, Qt::DropAction action, int row, int col, const QModelIndex& parent) override;

    private slots:
        void on_ScriptCompilerModel_dataChanged(const QModelIndex& tl, const QModelIndex& br);
    };
}

#endif