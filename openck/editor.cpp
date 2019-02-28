#include "editor.h"

Editor::Editor(int argc, char *argv[])
{
    viewMed.reset(new ViewMediator());
}

Editor::~Editor()
{

}
