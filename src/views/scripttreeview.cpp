/*
** scripttreeview.cpp
**
** Copyright � Beyond Skyrim Development Team, 2017.
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

#include <views/scripttreeview.h>
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <QSortFilterProxyModel>

#include <QDebug>

ScriptTreeView::ScriptTreeView(QWidget* parent)
    : QTreeView(parent)
{
    initActions();

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
    connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(on_ScriptTreeView_doubleClicked(const QModelIndex&)));
}

void ScriptTreeView::setModel(QAbstractItemModel* model)
{
    QTreeView::setModel(model);

    connect(selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(on_ScriptTreeView_selectionChanged(const QItemSelection&, const QItemSelection&)));
}

/**
* Shows context menu related to script items or global options when no item present under cursor.
* @brief Shows context menu related to scripts.
*/
void ScriptTreeView::showContextMenu(const QPoint& pos)
{
    QMenu menu(tr(""), this);

    QModelIndex index = indexAt(pos);

    menu.addAction(newScriptAction);
    if (index.isValid()) {

        //TODO: Find better way of passing index to actions.
        menu.addAction(compileAction);
        compileAction->setData(index);

        menu.addAction(disassembleAction);
        disassembleAction->setData(index);

        menu.addSeparator();

        menu.addAction(renameScriptAction);
        renameScriptAction->setData(index);

        menu.addAction(deleteScriptAction);
        deleteScriptAction->setData(index);
    }

    // Execute menu.
    menu.exec(mapToGlobal(pos));
}

/**
* Initialize and connect context menu actions.
* @brief Initialize and connect context menu actions.
*/
void ScriptTreeView::initActions()
{
    // Per item actions
    compileAction = new QAction(tr("Add to compile queue"), this);
    connect(compileAction, SIGNAL(triggered(bool)), this, SLOT(on_compileAction_triggered(bool)));

    disassembleAction = new QAction(tr("Disassemble"), this);

    renameScriptAction = new QAction(tr("Rename script"), this);
    connect(renameScriptAction, SIGNAL(triggered(bool)), this, SLOT(on_renameScriptAction_triggered(bool)));
    
    deleteScriptAction = new QAction(tr("Delete script"), this);
    connect(deleteScriptAction, SIGNAL(triggered(bool)), this, SLOT(on_deleteScriptAction_triggered(bool)));

    // Global actions.
    newScriptAction = new QAction(tr("New script"), this);
    connect(newScriptAction, SIGNAL(triggered(bool)), this, SLOT(on_newScriptAction_triggered(bool)));
}

/**
* Called when compile option is selected in context menu. Adds item to compilation queue.
* @brief Add item to compilation queue.
*/
void ScriptTreeView::on_compileAction_triggered(bool /* checked */)
{
    auto* cModel = model();
    if (cModel) {

        QModelIndex index = compileAction->data().toModelIndex();
        QModelIndex statusIndex = cModel->index(index.row(), 2);
        
        cModel->setData(statusIndex, static_cast<int>(2), Qt::UserRole);
    }
}

/**
* Called when 'New script' option selected in context menu. Opens a dialog to create a new script file.
* @brief Create new script file.
*/
void ScriptTreeView::on_newScriptAction_triggered(bool /* checked */)
{
    auto* cModel = static_cast<QSortFilterProxyModel*>(model())->sourceModel();
    if (cModel) {
        bool ok;
        QString scriptName = QInputDialog::getText(this, tr("New script"), tr("Script Name"), QLineEdit::Normal, "", &ok);

        if (ok && !scriptName.isEmpty()) {
            //TODO: Check for duplicate. Create script otherwise.

            int rc = cModel->rowCount();
            cModel->insertRow(rc);
            cModel->setData(cModel->index(rc, 0), scriptName, Qt::DisplayRole);
        }
    }
}

/**
* Called when 'Rename script' option selected in context menu. Opens a dialog for renaming script file.
* @brief Rename script file.
*/
void ScriptTreeView::on_renameScriptAction_triggered(bool /* checked */)
{
    auto* cModel = model();
    if (cModel) {
        bool ok;
        QString scriptName = QInputDialog::getText(this, tr("Rename script"), tr("Script Name"), QLineEdit::Normal, "", &ok);

        if (ok && !scriptName.isEmpty()) {

            QModelIndex index = renameScriptAction->data().toModelIndex();
            cModel->setData(index, scriptName, Qt::DisplayRole);

            renameScriptAction->setData({});
        }
    }
}

/**
* Called when 'Delete script' option selected in context menu. Prompts user if wanting to delete script file.
* @brief Delete script file.
*/
void ScriptTreeView::on_deleteScriptAction_triggered(bool /* checked */)
{
    auto* cModel = model();
    if (cModel) {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Delete script", "Are you sure you want to permenantly delete this script?", QMessageBox::No | QMessageBox::Yes, QMessageBox::No);

        if (reply == QMessageBox::Yes)
        {
            QModelIndex index = deleteScriptAction->data().toModelIndex();

            int row = index.row();
            cModel->removeRow(row);
        }
    }
}

/**
* Called when an item is double clicked in the view.
* @brief Item double click handler.
*/
void ScriptTreeView::on_ScriptTreeView_doubleClicked(const QModelIndex& index)
{
    auto* cModel = model();
    if (cModel) {

        //TODO: Temp code before proper filesystem integration. Remove when exists.
        emit scriptIndexChanged((index.isValid() ? 0 : -1));
    }
}

/**
* Called when the selection index is changed within in the view.
* @brief Selection changed handler.
*/
void ScriptTreeView::on_ScriptTreeView_selectionChanged(const QItemSelection&, const QItemSelection&)
{
    //TODO: Temp code before proper filesystem integration. Remove when exists.
    auto* cModel = model();
    if (cModel) {

        if(!currentIndex().isValid())
            emit scriptIndexChanged(-1);
    }
}