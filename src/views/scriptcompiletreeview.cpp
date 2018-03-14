#include <views/scriptcompiletreeview.h>
#include <QDropEvent>

ScriptCompileTreeView::ScriptCompileTreeView(QWidget* parent)
	: QTreeView(parent)
{
	setContextMenuPolicy(Qt::CustomContextMenu);
	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(showContextMenu(const QPoint&)));

	// Drag and Drop functionality.
	setDragEnabled(true);
	viewport()->setAcceptDrops(true);
	setDropIndicatorShown(true);
	setDragDropMode(QAbstractItemView::InternalMove);
}

void ScriptCompileTreeView::initActions()
{

}

void ScriptCompileTreeView::showContextMenu(const QPoint& pos)
{
	
}

void ScriptCompileTreeView::dropEvent(QDropEvent* ev)
{
	QModelIndex dropIdx = indexAt(ev->pos());

	if (!dropIdx.isValid())
		return;

	QTreeView::dropEvent(ev);
}