/*
** scripttreeview.h
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

#ifndef SCRIPTTREEVIEW_H
#define SCRIPTTREEVIEW_H

#include <QTreeView>

class ScriptTreeView : public QTreeView
{
    Q_OBJECT
public:
    ScriptTreeView(QWidget* parent = Q_NULLPTR);
    ScriptTreeView(const ScriptTreeView&) = default;
    ScriptTreeView& operator=(const ScriptTreeView&) = default;
    ~ScriptTreeView() = default;

    virtual void setModel(QAbstractItemModel* model) override;

private slots:
    void showContextMenu(const QPoint& pos);
    
    void on_compileAction_triggered(bool);

    void on_newScriptAction_triggered(bool);
    void on_renameScriptAction_triggered(bool);
    void on_deleteScriptAction_triggered(bool);

    void on_ScriptTreeView_doubleClicked(const QModelIndex& index);
    void on_ScriptTreeView_selectionChanged(const QItemSelection&, const QItemSelection&);

signals:
    void scriptIndexChanged(int index);

private:
    void initActions();

    QAction* compileAction{ nullptr };
    QAction* disassembleAction{ nullptr };

    QAction* renameScriptAction{ nullptr };
    QAction* deleteScriptAction{ nullptr };

    QAction* newScriptAction{ nullptr };
};

#endif