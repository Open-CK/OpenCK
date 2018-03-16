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

#include <QDebug>
#include <QSortFilterProxyModel>
#include <QFileSystemWatcher>
#include <QDir>
#include <QDirIterator>

ScriptManagerTab::ScriptManagerTab(QWidget* parent)
    : QWidget(parent), ui(new Ui::ScriptManagerTab)
{
    ui->setupUi(this);

    // Setup manager model and the filter proxy.
    managerProxyModel = new QSortFilterProxyModel(this);
    auto managerModel = new models::ScriptManagerModel(managerProxyModel);
    managerProxyModel->setSourceModel(managerModel);
    managerProxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);

    auto* managerTree = ui->treeViewScripts;
    managerTree->setModel(managerProxyModel);
    managerTree->hideColumn(models::ScriptManagerModel::COL_TMPPATH);
    managerTree->hideColumn(models::ScriptManagerModel::COL_PRIORITY);

    // Setup compiler model.
    compilerModel = new models::ScriptCompilerModel(this);
    compilerModel->setSourceModel(managerModel);

    auto* compilerTree = ui->treeViewScriptsCompile;
    compilerTree->setModel(compilerModel);
    compilerTree->hideColumn(models::ScriptManagerModel::COL_TMPPATH);
    compilerTree->hideColumn(models::ScriptManagerModel::COL_STATUS);
    compilerTree->hideColumn(models::ScriptManagerModel::COL_PRIORITY);
    compilerTree->sortByColumn(3, Qt::SortOrder::AscendingOrder);

    //TODO: Remove temp.
    connect(ui->treeViewScripts, SIGNAL(scriptIndexChanged(int)), ui->plainTextEditScriptEditor, SLOT(on_scriptIndexChanged(int)));

    // Pull in data.
    //QDir scriptFolder("data/source");
    QDirIterator it(QDir::currentPath() + "/data/source", QStringList() << "*.psc", QDir::Files, QDirIterator::NoIteratorFlags);

    while (it.hasNext()) {
        it.next();

        QString file = it.fileName();

        managerModel->insertRows(0, 1);
        managerModel->setData(managerModel->index(managerModel->rowCount() - 1, 0), file, Qt::UserRole);
    }
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

void ScriptManagerTab::on_pushButtonCompile_released()
{
    for (unsigned int i = 0; i < compilerModel->rowCount(); i++) {
        QModelIndex idx = compilerModel->index(i, 0);
        QString data = compilerModel->data(idx, Qt::UserRole).toString();
        qDebug() << "Compiling " << data;

        //TODO: Hook up papyrus compiler when settings available.
    }
}