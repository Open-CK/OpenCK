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

void ScriptTreeView::on_compileAction_triggered(bool /* checked */)
{
    auto* cModel = model();
    if (cModel) {

        QModelIndex index = compileAction->data().toModelIndex();
        
        QModelIndex statusIndex = cModel->index(index.row(), 2);
        QModelIndex priorityIndex = cModel->index(index.row(), 3);
        
        cModel->setData(statusIndex, static_cast<int>(2), Qt::UserRole);
        cModel->setData(priorityIndex, 0, Qt::UserRole);
    }
}

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

void ScriptTreeView::on_ScriptTreeView_doubleClicked(const QModelIndex& index)
{
    auto* cModel = model();
    if (cModel) {

        //TODO: Temp code before proper filesystem integration. Remove when exists.
        emit scriptIndexChanged((index.isValid() ? 0 : -1));
    }
}

void ScriptTreeView::on_ScriptTreeView_selectionChanged(const QItemSelection&, const QItemSelection&)
{
    //TODO: Temp code before proper filesystem integration. Remove when exists.
    auto* cModel = model();
    if (cModel) {

        if(!currentIndex().isValid())
            emit scriptIndexChanged(-1);
    }
}