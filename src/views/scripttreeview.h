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
    QAction* renameScriptAction{ nullptr };
    QAction* deleteScriptAction{ nullptr };

    QAction* newScriptAction{ nullptr };
};

#endif