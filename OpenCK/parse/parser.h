/*
** parser.h
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

//!@file parser.h Header for the .esm and .esp parser.

#ifndef PARSER_H
#define PARSER_H

#include <QByteArray>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "tes4form.h"
#include "readfile.h"

namespace Parse
{
    class Parser;
}

/**
 * The Parser class parses .esm/.esp files via parse(QStringList, QString)
 * @brief The class that parses .esm/.esp files.
 */
class Parser : public QObject
{
    Q_OBJECT

public:
    void parse(QStringList list, QString activePath);
    void parse(QStringList list);
    void warn(QString message);
    static Parser& getParser();

public slots:

signals:
    void addForm(Form* form, int fileNumber);
    void addFile(QString name);
    void updateFileModel();

private:
    //SINGLETON STUFF!
    Parser();

    /**
     * Prevent copying.
     * @brief Prevent copying.
     */
    Parser(const Parser&) = delete;
    /**
     * Prevent self assignments.
     * @brief Prevent self assignments.
     * @return Nothing.
     */
    Parser& operator=(const Parser&) = delete;
    /**
     * Prevent really weird copies.
     * @brief Prevent really weird copies.
     */
    Parser(Parser&&) = delete;
    /**
     * Prevent really weird assignments.
     * @brief Prevent really weird assignments.
     * @return Nothing.
     */
    Parser& operator=(Parser&&) = delete;
};

#endif // PARSER_H
