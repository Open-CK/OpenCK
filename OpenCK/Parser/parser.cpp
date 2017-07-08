#include "parser.h"

/**
 * Parses a list of .esm and .esp files (based on file path).
 * @brief Parser::parse
 * @param list The list of file paths to be parsed.
 */
void Parser::parse(QStringList list)
{
    qDebug() << list << " has begun parsing.";
    //todo
}

/**
 * Retruns a parsed collection of .esm and .esp files.
 * @brief Parser::getParsed
 * @return The parsed object based on #parse
 * @see Parser::parse
 */
Parsed Parser::getParsed()
{
    return *parsed;
}
