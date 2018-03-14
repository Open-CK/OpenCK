#ifndef SCRIPTCOMPILETREEVIEW_H
#define SCRIPTCOMPILETREEVIEW_H

#include <QTreeView>

class ScriptCompileTreeView : public QTreeView
{
    Q_OBJECT
public:
    ScriptCompileTreeView(QWidget* parent = Q_NULLPTR);
    ScriptCompileTreeView(const ScriptCompileTreeView&) = default;
    ScriptCompileTreeView& operator=(const ScriptCompileTreeView&) = default;
    ~ScriptCompileTreeView() = default;

private slots:
    void showContextMenu(const QPoint& pos);

private:
    void initActions();

    virtual void dropEvent(QDropEvent* ev) override;
};

#endif