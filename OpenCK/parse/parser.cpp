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
#include "formgroup.h"

//!@file parser.cpp Source for the .esm and .esp file parser.
static QDataStream in;

/**
 * Construct the parser and ensure we can't accidently delete stuff via pointers.
 * This exists solely to create an instance for getParser.
 * @brief Construct the parser.
 * @see Parser::getParser()
 */
Parser::Parser()
{

}

/**
 * Parses a list of .esm and .esp files (based on file path).
 * Defaults activePath to the first element of the list.
 * @brief Parses a list of .esm and .esp files.
 * @param list The list of files to be parsed.
 * @see Parser::parse(QStringList,QString)
 */
void Parser::parse(QStringList list)
{
    qDebug() << "No active file, defaulting.";
    warn("There is no active file. Defaulting Active File to first selected element.");
    parse(list,list.at(0));
}

/**
 * Parses a list of .esm and .esp files (based on file path) with a specified active file.
 * @brief Parses a list of .esm and .esp files with an active file.
 * @param list The list of file paths to be parsed.
 * @param activePath the Active File (the file on which changes are applied to).
 */
void Parser::parse(QStringList list, QString activePath)
{
    for(int i = 0; i < list.size(); i++) {
        QFile file(list.at(i));
        QFileInfo info(file.fileName());
        QString name(info.fileName());
        emit addFile(name);

        qDebug() << list.at(i) << " started parsing.";
        if(!file.open(QIODevice::ReadOnly)) {
            warn(name.append(" could not be opened."));
            continue;
        }

        in.setDevice(&file);

        //Begin parsing header record
        TES4Form* TES4 = new TES4Form;
        TES4->load(&in, i);
        emit addForm(TES4, i);

        int j = 0;

        while (j <= 3) { //Loop condition temporary
            QByteArray buffer = nullptr;
            quint32 type = qToBigEndian(ReadFile::readUInt32(&in, &buffer));

                switch (type) {
                    case 'GRUP':
                        FormGroup* group = new FormGroup(&in, &buffer);
                        connect(group, &FormGroup::addForm, &Parser::getParser(),
                                &Parser::addGroupForm);
                        group->load(&in, i);
                        qDebug("Breakpoint here");

                        break;
                }

            ++j;
        }
    }

    emit updateFileModel();
}

/**
 * Gives a warning to the user with a given string.
 * @brief Gives a warning to the user with a given string.
 * @param message Message to be displayed in the warning box.
 */
void Parser::warn(QString message)
{
    QMessageBox* msgBox = new QMessageBox;
    msgBox->setSizeIncrement(600, 400);
    msgBox->setText(message);
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setIcon(QMessageBox::Warning);
    msgBox->setWindowIcon(QIcon(":/openck32x32.png"));
    msgBox->exec();
}

/**
 * Get the instance of the parser.
 * @brief Get the instance of the parser.
 * @return The instance of the parser.
 */
Parser& Parser::getParser()
{
    static Parser parser;
    return parser;
}

void Parser::addGroupForm(Form *form, int fileNumber)
{
    emit addForm(form, fileNumber);
}
