#include <views/scripttreeview.h>
#include <QMenu>
#include <QInputDialog>
#include <QDir>
#include <QSortFilterProxyModel>

ScriptTreeView::ScriptTreeView(QWidget* parent)
    : QTreeView(parent)
{
    initActions();

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

    connect(this, SIGNAL(doubleClicked(const QModelIndex&)), this, SLOT(on_ScriptTreeView_doubleClicked(const QModelIndex&)));
}

void ScriptTreeView::showContextMenu(const QPoint& pos)
{
    QMenu menu(tr(""), this);

    QModelIndex index = indexAt(pos);
    if (index.isValid()) {
        menu.addAction(compileAction);
    } else {
        menu.addAction(newScriptAction);
    }

    menu.exec(mapToGlobal(pos));
}

void ScriptTreeView::initActions()
{
    // Per item actions
    compileAction = new QAction(tr("Add to compile queue"), this);

    // Global actions.
    newScriptAction = new QAction(tr("New Script"), this);
    connect(newScriptAction, SIGNAL(triggered(bool)), this, SLOT(on_newScriptAction_triggered(bool)));
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

void ScriptTreeView::on_ScriptTreeView_doubleClicked(const QModelIndex& index)
{
    auto* cModel = model();
    if (cModel) {

        // TODO: pull up script record.
        emit scriptIndexChanged();
    }
}