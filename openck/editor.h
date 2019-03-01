#ifndef EDITOR_H
#define EDITOR_H

#include "view/viewmediator.h"

#include <QSettings>

#include <memory>

class Editor
{
public:
    Editor(int argc, char *argv[]);
    ~Editor();

private:
    QString getDataPath(const QString& applicationName);

    std::unique_ptr<ViewMediator> viewMed;
};

#endif // EDITOR_H
