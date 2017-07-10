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

static QList<Parsed> parsed;

/**
 * A debug function to test things without actually writing to file and screwing things up.
 */
void Parser::debug(QStringList list)
{
    for(int i = 0; i < list.size(); i++) {
        QFile file(list.at(i));
        QFileInfo info(file.fileName());
        QString name(info.fileName());
        qDebug() << list.at(i) << " started parsing.";
        if(!file.open(QIODevice::ReadOnly)) {
            warn(name.append(" could not be opened."));
            continue;
        }
        QDataStream in(&file);
        TES4Record* TES4 = new TES4Record;
        QByteArray buffer;
        buffer.resize(4);
        in.readRawData(buffer.data(),4);
        char* inType = buffer.data();
        qDebug() << "Record type is " << inType;
        TES4->type = inType;
    }
}

/**
 * Parses a list of .esm and .esp files (based on file path).
 * Defaults activePath to the first element of the list.
 * @brief Parser::parse
 * @param list The list of files to be parsed.
 * @see Parser::parse(QStringList,QString)
 */
void Parser::parse(QStringList list)
{
    qDebug() << "No active file, defaulting.";
    warn("There is no active file. Defaulting Active File to first selected element.");
    parse(list,list.at(0));
    //debug(list);
}

/**
 * Parses a list of .esm and .esp files (based on file path) with a specified active file.
 * @brief Parser::parse
 * @param list The list of file paths to be parsed.
 * @param activePath the Active File (the file on which changes are applied to).
 */
void Parser::parse(QStringList list, QString activePath)
{   
    for(int i = 0; i < list.size(); i++) {
        QFile file(list.at(i));
        QFileInfo info(file.fileName());
        QString name(info.fileName());
        qDebug() << list.at(i) << " started parsing.";
        if(!file.open(QIODevice::ReadOnly)) {
            warn(name.append(" could not be opened."));
            continue;
        }
        QDataStream in(&file);
        TES4Record* TES4 = new TES4Record;
        QByteArray buffer;
        buffer.resize(4);
        in.readRawData(buffer.data(),4);
        char* inType = buffer.data();
        qDebug() << "Decoded item: Current record type is --" << inType;
        TES4->type = inType;


//      NEXT ITEM TO PARSE IS UINT32_T: DATASIZE
//      PLEASE CHECK RECORDPARENT.H AND TES4RECORD.H TO VIEW DATA TYPES AND ORDER

//        while(!in.atEnd()) {
//            //get the non-header data.
//        }

//        Parsed justParsed(TES4 /* more data, but just doing headerdata right now */);
//        parsed.append(justParsed);
    }
}

/**
 * Returns a parsed collection of .esm and .esp files.
 * @brief Parser::getParsed
 * @return The parsed object based on #parse
 * @see Parser::parse(QStringList)
 */
QList<Parsed> Parser::getParsed()
{
    return parsed;
}

void Parser::warn(QString message)
{
    QMessageBox *msgBox = new QMessageBox;
    msgBox->setSizeIncrement(600, 400);
    msgBox->setText(message);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowIcon(QIcon(":/openck32x32.png"));
    msgBox->exec();
}

