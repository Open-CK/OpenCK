from bs4 import BeautifulSoup

HEAD = """/*
** functionindexes.h
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
** Created Date: 19-Oct-2017
*/

#ifndef FUNCTIONINDEXES_H
#define FUNCTIONINDEXES_H

#include <QMap>
#include <QString>

namespace esx
{
    static QMap<quint32, QString> functionIndexes
    {
        //GENERATED CODE FOLLOWS — DO NOT EDIT
        """

FOOT = """
    };
}

#endif // FUNCTIONINDEXES_H
"""

LOC = "../src/data/functionindexes.h"
SOURCE = "../res/gen/func"

def gen():
    with open(SOURCE, 'r') as file:
        text = file.read()

    ids = []
    names = []
    soup = BeautifulSoup(text, 'html.parser')

    for tag in soup.find_all('strong'):
        names.append(tag.string)

    for tag in soup.find_all('td', {'class': 'id'}):
        ids.append(tag.string)

    string = ""
    i = 0;
    while True:
        string = string + "{{{0!s}, \"{1!s}\"}},\n        ".format(ids[i], names[i])

        if i >= len(ids) - 1 or i >= len(names) - 1:
            string = string[:-4]
            break

        i = i + 1

    string = HEAD + string + FOOT

    file = open(LOC, "w")
    file.truncate()
    file.write(string)
    file.close()


if __name__ == '__main__':
    gen()
