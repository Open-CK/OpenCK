#include "editor.h"
#include "../ui/ui_editor.h"

Editor::Editor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::editor)
{
    ui->setupUi(this);
}

Editor::~Editor()
{
    delete ui;
}
