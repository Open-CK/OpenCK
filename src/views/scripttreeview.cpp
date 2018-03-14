#include <views/scripttreeview.h>
#include <QMenu>

ScriptTreeView::ScriptTreeView(QWidget* parent)
    : QTreeView(parent)
{
    initActions();

    this->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));
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
}