#ifndef PARSER_H
#define PARSER_H

#include <QStringList>
#include <QDebug>
#include "parsed.h"

class Parser
{

public:
    static void parse(QStringList list);
    static Parsed getParsed();
private:
    static Parsed *parsed;
};

#endif // PARSER_H
