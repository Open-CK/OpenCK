/*
** formerrorhandler.h
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
** Created Date: 06-Jul-2017
*/

//!@file formerrorhandler.h for error reporting in forms

#ifndef FORMERRORHANDLER_H
#define FORMERRORHANDLER_H

#include <QDialog>
#include <QDebug>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFileDialog>
#include <QPushButton>

namespace esx
{
	/**
	 * The class for the error handler for forms
	 * @brief The form error handler class.
	 */
	class FormErrorHandler : public QObject
	{

	public:
		FormErrorHandler(QString message = " ");
        ~FormErrorHandler() {}
		bool getIgnore();

	private:

		bool displayError(QString message);
		bool ignore = false;
	};

}
#endif // FORMERRORHANDLER_H
