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

protected:

public slots:
	void showContextMenu(const QPoint& pos);
private:
	void initActions();

	QAction* compileAction{ nullptr };
	QAction* newScriptAction{ nullptr };
};

#endif