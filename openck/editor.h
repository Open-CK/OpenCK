#ifndef EDITOR_H
#define EDITOR_H

#include "view/viewmediator.h"
#include "model/documentmediator.h"

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
    std::unique_ptr<DocumentMediator> docMed;
};

#endif // EDITOR_H
