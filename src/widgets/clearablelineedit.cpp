/*
** clearablelineedit.cpp
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

#include <widgets/clearablelineedit.h>
#include <QToolButton>
#include <QStyle>

ClearableLineEdit::ClearableLineEdit(QWidget* parent)
    : QLineEdit(parent)
{
    clearButton = new QToolButton(this);
    QIcon clearIcon(":/lineedit-cancel-button32x32.png");
    clearButton->setIcon(clearIcon);
    clearButton->setCursor(Qt::ArrowCursor);
    clearButton->setStyleSheet("QToolButton { border: none; }");
    clearButton->hide();

    // Apply to line edit.
    int w = style()->pixelMetric(QStyle::PixelMetric::PM_DefaultFrameWidth);
    setStyleSheet(QString("QLineEdit { padding-right: %1px; }").arg(clearButton->sizeHint().width() + w + 1));
    QSize minSize = minimumSizeHint();
    setMinimumSize(qMax(minSize.width(), clearButton->sizeHint().width() + w * 2 + 2), qMax(minSize.height(), clearButton->sizeHint().height()));

    // Connect button signals.
    connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateClearButton(const QString&)));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(on_clearButton_clicked()));
}

void ClearableLineEdit::resizeEvent(QResizeEvent* ev)
{
    QSize size = clearButton->sizeHint();
    int w = style()->pixelMetric(QStyle::PixelMetric::PM_DefaultFrameWidth);
    clearButton->move(rect().right() - w - size.width(), (rect().bottom() + 1 - size.height()) / 2);
}

void ClearableLineEdit::updateClearButton(const QString& text)
{
    clearButton->setVisible(!text.isEmpty());
}

void ClearableLineEdit::on_clearButton_clicked()
{
    clear();
    emit clearButtonClicked();
}