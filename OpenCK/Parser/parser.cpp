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
        TES4Data header;
        QByteArray buffer;
        buffer.resize(4);
        in.readRawData(buffer.data(),4);
        bool success;
        float ver = buffer.toFloat(&success);
        if(!success) {
            warn("Version error occured.");
            qDebug() << "Version is " << ver;
            continue;
        }
        qDebug() << "Version is " << ver;
        header.version = ver;

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
    qDebug() << list << " has begun parsing. \nThe active file is " << activePath;
    for(int i = 0; i < list.size(); i++) {
        QFile file(list.at(i));
        qDebug() << list.at(i) << " started parsing.";
        if(!file.open(QIODevice::ReadWrite)) {
            QFileInfo info(file.fileName());
            QString string(info.fileName());
            warn(string + " could not be opened.");
            continue;
        }
        QDataStream in(&file);
        TES4Data header;

        //THIS IS CURRENTLY BROKEN!
        QByteArray buffer;
        buffer.resize(4);
        in.readRawData(buffer.data(),4);
        bool success;
        float ver = buffer.toFloat(&success);
        if(!success) {
            warn("Version error occured.");
            continue;
        }
        qDebug() << "Version is " << ver;
        header.version = ver;
        //TODO: get more header data and like for notoh to not be stupid and fix stuff

        while(!in.atEnd()) {
            //get the non-header data.
        }

        Parsed justParsed(header /* more data, but just doing headerdata right now */);
        parsed.append(justParsed);
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

