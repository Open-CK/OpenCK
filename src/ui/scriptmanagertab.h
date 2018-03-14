#ifndef SCRIPTMANAGERTAB_H
#define SCRIPTMANAGERTAB_H

#include <QWidget>

namespace Ui
{
    class ScriptManagerTab;
}

namespace models
{
    class ScriptCompilerModel;
    class ScriptManagerModel;
}

class QSortFilterProxyModel;
class ScriptManagerTab
    : public QWidget
{
    Q_OBJECT
public:
    ScriptManagerTab(QWidget* parent = Q_NULLPTR);
    ScriptManagerTab(const ScriptManagerTab&) = default;
    ScriptManagerTab& operator=(const ScriptManagerTab&) = default;
    ~ScriptManagerTab() = default;

private slots:
    void on_lineEditScriptFilter_returnPressed();
    void on_lineEditScriptFilter_clearButtonClicked();

private:
    Ui::ScriptManagerTab* ui;

    QSortFilterProxyModel* managerProxyModel{ nullptr };
    models::ScriptCompilerModel* compilerModel{ nullptr };
};

#endif