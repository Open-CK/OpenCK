/*
** datawindow.h
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

//!@file datawindow.h Header for Data UI Window.

#ifndef DATAWINDOW_H
#define DATAWINDOW_H

#include <QDialog>
#include <QDir>
#include <QDebug>
#include <QTableView>
#include <QStandardItemModel>
#include <QMessageBox>
#include "parser.h"

namespace Ui
{
    class DataWindow;
}

/**
 * The class for the data window opened from the main window.
 * @brief The data window class.
 */
class DataWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataWindow(QWidget* parent = 0);
    ~DataWindow();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_fileListView_doubleClicked(const QModelIndex &index);
    void on_makeActiveButton_clicked();

private:
    /**
     * Pointer to the generated Qt Data window from the UI Designer.
     * @brief Pointer to the generated Qt ui.
     */
    Ui::DataWindow* ui;
    /**
     * The table populated inside the data window of .esm and .esp files.
     * @brief The table inside the data window.
     */
    QTableView* table;
    /**
     * The table view model inside the data window.
     * @brief The table view model.
     */
    QStandardItemModel* model;
    /**
     * The working directory of .esm and .esp files.
     * @brief The data directory.
     */
    QDir workingDir;

    void searchFiles();
    void formatListView(int quant, QStringList fileList);
    void populateListView(int quant, QStringList fileList, QTableView* table);
    void showFailure(QString message);
    void changeStatusColumn(QModelIndexList indexes);
    void updateCheckBoxes(QModelIndexList indexes);
};

#endif // DATAWINDOW_H
