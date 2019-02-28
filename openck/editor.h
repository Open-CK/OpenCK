#ifndef EDITOR_H
#define EDITOR_H

#include "view/viewmediator.h"

#include <memory>

class Editor
{
public:
    Editor(int argc, char *argv[]);
    ~Editor();

private:
    std::unique_ptr<ViewMediator> viewMed;
};

#endif // EDITOR_H
