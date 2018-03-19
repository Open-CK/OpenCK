/*
** scriptmanagertab.cpp
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
** Created Date: 04-Jul-2017
*/

#include <ui/scriptmanagertab.h>
#include "ui_scriptmanagertab.h"

#include <models/scriptmanagermodel.h>
#include <models/scriptcompilermodel.h>

#include <widgets/scripteditor.h>

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QFileSystemWatcher>
#include <QDir>
#include <QDirIterator>
#include <QInputDialog>

ScriptManagerTab::ScriptManagerTab(QWidget* parent)
    : QWidget(parent), ui(new Ui::ScriptManagerTab)
{
    ui->setupUi(this);

    // Setup manager model and the filter proxy.
    using SMCol = models::ScriptManagerModel::ColumnType;

    managerModel = new models::ScriptManagerModel(this);
    managerProxyModel = new QSortFilterProxyModel(managerModel);
    managerProxyModel->setSourceModel(managerModel);
    managerProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    managerProxyModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    managerProxyModel->setDynamicSortFilter(true);

    auto* managerTree = ui->treeViewScripts;
    managerTree->setModel(managerProxyModel);
    managerTree->hideColumn(SMCol::COL_TMPPATH);
    managerTree->hideColumn(SMCol::COL_PRIORITY);

    // Setup compiler model.
    compilerModel = new models::ScriptCompilerModel(managerModel);
    compilerModel->setSourceModel(managerModel);

    auto* compilerTree = ui->treeViewScriptsCompile;
    compilerTree->setModel(compilerModel);
    compilerTree->hideColumn(SMCol::COL_TMPPATH);
    compilerTree->hideColumn(SMCol::COL_STATUS);
    compilerTree->hideColumn(SMCol::COL_PRIORITY);
    compilerTree->sortByColumn(SMCol::COL_PRIORITY, Qt::SortOrder::AscendingOrder);

    // Pull in script data.
    scriptsPath = QDir::currentPath() + "/data/source/";
    QDirIterator it(scriptsPath, QStringList() << "*.psc", QDir::Files, QDirIterator::NoIteratorFlags);

    while (it.hasNext()) {
        it.next();

        QString file = it.fileName();
        int extLocation = file.lastIndexOf('.');
        file = file.left(extLocation);

        managerModel->insertRows(managerModel->rowCount(), 1);
        managerModel->setData(managerModel->index(managerModel->rowCount() - 1, SMCol::COL_NAME), file, Qt::UserRole);
    }
    managerProxyModel->sort(SMCol::COL_NAME, Qt::SortOrder::AscendingOrder);
}

/**
* Called when the return key is pressed whilst the script filter line edit is active.
* @brief Handle return key for script filter.
*/
void ScriptManagerTab::on_lineEditScriptFilter_returnPressed()
{
    if (managerProxyModel) {
        managerProxyModel->setFilterFixedString(ui->lineEditScriptFilter->text());
    }
}

/**
* Called when the clear button is pressed in the script filter line edit.
* @brief Clear filter line edit.
*/
void ScriptManagerTab::on_lineEditScriptFilter_clearButtonClicked()
{
    if (managerProxyModel) {
        managerProxyModel->setFilterFixedString("");
    }
}

/**
* Called when the compile all button is pressed. Will spawn compilation threads.
* @brief Spawn compilation threads from queue.
*/
void ScriptManagerTab::on_pushButtonCompile_released()
{
    for (unsigned int i = 0; i < compilerModel->rowCount(); i++) {
        QModelIndex idx = compilerModel->index(i, 0);
        QString data = compilerModel->data(idx, Qt::UserRole).toString();
        qDebug() << "Compiling " << data;

        //TODO: Hook up papyrus compiler when settings available.
    }
}

/**
* Called when an item in the script tree view is double clicked. Either switches to an active tab or creates a new one.
* @brief Switches or creates a script tab.
*/
void ScriptManagerTab::on_treeViewScripts_doubleClicked(const QModelIndex& index)
{
    if (!index.isValid())
        return;

    QModelIndex nameIndex = managerProxyModel->index(index.row(), 0);
    QString scriptName = managerProxyModel->data(nameIndex, Qt::UserRole).toString();

    // Search for an active editor before creating a new one.
    auto* tabBar = ui->tabWidgetScriptEditor->tabBar();
    int numTabs = tabBar->count();
    int foundIndex = -1;
    for (int i = 0; i < numTabs && foundIndex == -1; i++) {
        if (tabBar->tabText(i) == scriptName) {
            foundIndex = i;
        }
    }

    if (foundIndex != -1) {
        // Switch to active tab.
        ui->tabWidgetScriptEditor->setCurrentIndex(foundIndex);
    } else {
        // Create a new tab and make it active.
        ui->tabWidgetScriptEditor->addTab(new ScriptEditor(scriptsPath + scriptName + ".psc", ui->tabWidgetScriptEditor), scriptName);
        ui->tabWidgetScriptEditor->setCurrentIndex(ui->tabWidgetScriptEditor->count() - 1);
    }
}

/**
* Called when new script action is triggered in scripttreeview. Adds new script to the model.
* @brief Adds a new script to the model.
*/
void ScriptManagerTab::on_treeViewScripts_newScriptTriggered(bool /* checked */)
{
    if (managerModel) {
        bool ok;
        QString scriptName = QInputDialog::getText(this, tr("New script"), tr("Script Name"), QLineEdit::Normal, "", &ok);

        if (ok && !scriptName.isEmpty()) {
            //TODO: Check for duplicate. Create script otherwise.

            int rc = managerModel->rowCount();
            managerModel->insertRow(rc);
            managerModel->setData(managerModel->index(rc, 0), scriptName, Qt::DisplayRole);
        }
    }
}

/**
* Called when a tab has its close button pressed. Will schedule the tab for deletion.
* @brief Closes an active script tab.
*/
void ScriptManagerTab::on_tabWidgetScriptEditor_tabCloseRequested(int index)
{
    // TODO: Prompt user when contents changed in widget.
    // Remove tab from stack and delete it.
    ui->tabWidgetScriptEditor->widget(index)->deleteLater();
}