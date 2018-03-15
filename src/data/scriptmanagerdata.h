#ifndef SCRIPTMANAGERDATA_H
#define SCRIPTMANAGERDATA_H

#include <QString>

enum class ScriptStatus
{
    NONE,
    DIRTY,
    COMPILE_WAIT,
    COMPILE_SUCCESS,
    COMPILE_FAIL
};

struct ScriptManagerData
{
    QString name;
    QString tmpPath;
    ScriptStatus status{ ScriptStatus::NONE };
    int priority{ -1 };
};

#endif