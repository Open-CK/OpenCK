/*
** formerrorhandler.cpp
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
** Created Date: 17-Mar-2018
*/


#include <data/formerrorhandler.h>


namespace esx
{
	//!@file formerrorhandler.h for error reporting in forms

	/**
	 * Displays a dialog window upon form error
	 * @brief Constructs a dialog window and retains output.
	 * @param message The message to present to the user.
	 */
	FormErrorHandler::FormErrorHandler(QString message)
	{
		if (displayError(message)) {
			ignore = true;
		}
	}

	bool FormErrorHandler::getIgnore()
	{
		return ignore;
	}

	bool FormErrorHandler::displayError(QString message)
	{
		QMessageBox* msg = new QMessageBox;
		msg->setSizeIncrement(600, 400);
		msg->setText(message);
        msg->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
		msg->setIcon(QMessageBox::Warning);
		msg->setWindowIcon(QIcon(":/openck32x32.png"));
        return (msg->exec() == QMessageBox::Yes);
	}
}
