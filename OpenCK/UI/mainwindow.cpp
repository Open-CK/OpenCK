/*
** mainwindow.cpp
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
** Created Date: 04-Jul-2017
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("OpenCK");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    qDebug() << tr("User hit exit from File menu");
	close();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox *msgBox;
    msgBox = new QMessageBox;
    msgBox->setSizeIncrement(600,400);
    msgBox->setText(tr("OpenCK Version Kek\n(c) 2017 Beyond Skyrim Development Team\nThis project's source code is viewable at https://github.com/Beyond-Skyrim/OpenCK\nHappy Modding!")); //TODO: Version String!
    msgBox->setStandardButtons(QMessageBox::Ok);
    msgBox->setWindowIcon(QIcon(":/openck32x32.png"));
    msgBox->exec();
}

void MainWindow::on_actionContents_triggered()
{
    QString link = "http://www.creationkit.com/";
    QDesktopServices::openUrl(QUrl(link));
}

void MainWindow::on_actionData_triggered()
{
    DataWindow window;
    window.exec();
}
