/*
** parser.cpp
**
** Copyright © Beyond Skyrim Development Team, 2017.
** This file is part of OPENCK (https://github.com/Beyond-Skyrim/openck)
**
** OpenCK is free software; this file may be used under the terms of the GNU
** General Public License version 3.0 or later as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** OpenCK is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**
** Please review the following information to ensure the GNU General Public
** License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** You should have received a copy of the GNU General Public License version
** 3.0 along with OpenCK; if not, write to the Free Software Foundation,
** Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** Created Date: 08-Jul-2017
*/

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
 * @see Parser::parse(QStringList)
 */
Parsed Parser::getParsed()
{
    return *parsed;
}
