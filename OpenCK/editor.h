#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

namespace Ui {
class editor;
}

class Editor : public QMainWindow
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

private:
    Ui::editor *ui;
};

#endif // EDITOR_H
