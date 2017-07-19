/*
** cellview.h
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

//!@file Header for Cell View in the UI.

#ifndef CELLVIEW_H
#define CELLVIEW_H

#include <QWidget>

namespace Ui
{
    class CellView;
}

/**
 * The Cell View in the UI is how all cells are accessed in the Creation Kit.
 * @brief The view from which cells are accessed.
 */
class CellView : public QWidget
{
     Q_OBJECT

public:
    explicit CellView(QWidget* parent = 0);
    ~CellView();
private:
    /**
     * Pointer to the Qt generated UI class via the UI designer.
     * @brief The Qt generated UI class.
     */
    Ui::CellView* ui;
};

#endif // CELLVIEW_H
