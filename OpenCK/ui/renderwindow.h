/*
** renderwindow.h
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
** Created Date: 18-Jul-2017
*/

//!@file renderwindow.h Header for Render UI Window.

#ifndef RENDERWINDOW_H
#define RENDERWINDOW_H

#include <QMainWindow>

namespace Ui
{
    class RenderWindow;
}

/**
 * The Render Window in the UI.
 * @brief The Render Window in the UI.
 */
class RenderWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RenderWindow(QWidget* parent = 0);
    ~RenderWindow();

private:

    /**
     * Pointer to the Qt Generated Render Window in the UI via the UI designer.
     * @brief The Qt Generated Render Window in the UI.
     */
    Ui::RenderWindow* ui;
};

#endif // RENDERWINDOW_H
