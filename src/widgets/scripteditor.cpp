/*
** scripteditor.cpp
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

#include <widgets/scripteditor.h>
#include <widgets/papyrushighlighter.h>
#include <QPainter>
#include <QTextBlock>
#include <QInputDialog>

ScriptEditor::ScriptEditor(QWidget* parent)
    : QPlainTextEdit(parent)
{
    setWordWrapMode(QTextOption::NoWrap);
    lineNumberWidget = new LineNumberWidget(this);

    on_blockCountChanged(0);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(on_blockCountChanged(int)));
    connect(this, SIGNAL(updateRequest(const QRect&, int)), this, SLOT(on_updateRequest(const QRect&, int)));

    syntaxHighlighter = new PapyrusHighlighter(document());

    this->setTabStopWidth(4 * fontMetrics().width(' '));
}

void ScriptEditor::resizeEvent(QResizeEvent* ev)
{
    QPlainTextEdit::resizeEvent(ev);

    QRect contentBounds = contentsRect();
    lineNumberWidget->setGeometry(QRect(contentBounds.left(), contentBounds.top(), getLineNumberAreaWidth(), contentBounds.height()));
}

/**
* Intercepts key press events to the editor allowing for hotkeys.
* @brief Intercepts key presses.
*/
void ScriptEditor::keyPressEvent(QKeyEvent* ev)
{
    switch (ev->key()) {
    case Qt::Key_G: // TODO: Change from hardcoded to option in preferences menu.
        if (ev->modifiers() == Qt::ControlModifier) {
            executeGoToLine();
        }
        break;
    }

    QPlainTextEdit::keyPressEvent(ev);
}

void ScriptEditor::wheelEvent(QWheelEvent* ev)
{
    // Handle font zoom.
    if (ev->modifiers() == Qt::ControlModifier) {
        
        // Get current font size.
        auto f = font();
        int currentSize = f.pointSize();

        // Get the mouse wheel delta.
        QPoint deg = ev->angleDelta();

        if (!deg.isNull()) {

            if (deg.y() > 0) {
                f.setPointSize(currentSize + 1);
            } else if (deg.y() < 0 && currentSize > 1) {
                f.setPointSize(currentSize - 1);
            }

            // Update font and tab width.
            setFont(f);
            this->setTabStopWidth(4 * fontMetrics().width(' '));
            lineNumberWidget->setFont(f);

            ev->accept();
        }
    } else {
        // We haven't handled the event so pass it down the line.
        QPlainTextEdit::wheelEvent(ev);
    }
}

/**
* Refreshes the viewport with new margins when the line count changes.
* @brief Refreshes viewport on line count change.
*/
void ScriptEditor::on_blockCountChanged(int blocks)
{
    setViewportMargins(getLineNumberAreaWidth(), 0, 0, 0);
}

void ScriptEditor::on_updateRequest(const QRect& rect, int dy)
{
    // Viewport scroll.
    if (dy) {
        lineNumberWidget->scroll(0, dy);
    }
    else {
        lineNumberWidget->update(0, rect.y(), lineNumberWidget->width(), rect.height());
    }

    if (rect.contains(viewport()->rect())) {
        on_blockCountChanged(0);
    }
}

void ScriptEditor::paintLineNumbers(QPaintEvent* ev)
{
    QPainter painter(lineNumberWidget);

    QTextBlock currentBlock = firstVisibleBlock();
    int top = static_cast<int>(blockBoundingGeometry(currentBlock).translated(contentOffset()).top());
    int bottom = top + static_cast<int>(blockBoundingRect(currentBlock).height());

    quint64 currentLine = currentBlock.blockNumber();

    QFont font = painter.font();
    while (currentBlock.isValid()) {
        // Only render when block is visible.
        if (currentBlock.isVisible()) {
            //painter.drawEllipse(0, top, 32, 32);

            painter.drawText(0, top, lineNumberWidget->width() - LINENUMBER_PADDING, fontMetrics().height(), Qt::AlignRight, QString::number(currentLine));
        }

        // Grab the next block of text.
        currentBlock = currentBlock.next();
        ++currentLine;
        top = bottom;
        bottom = top + static_cast<int>(blockBoundingRect(currentBlock).height());
    }
}

int ScriptEditor::getLineNumberAreaWidth() const
{
    int digits = 1;
    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }

    int space = (3 + fontMetrics().width(QLatin1Char('9')) * digits) + LINENUMBER_PADDING;

    return space;
}

/**
* Takes user input and moves the text cursor to the specified line.
* @brief Moves the text cursor to specified line.
*/
void ScriptEditor::executeGoToLine()
{
    bool ok;
    int line = QInputDialog::getInt(this, "Go to line", "Line", 0, 0, blockCount() - 1, 1, &ok);

    if (ok) {
        QTextCursor cursor(document()->findBlockByLineNumber(line));
        setTextCursor(cursor);
    }
}

/**
* Displays line numbers to the user.
* @brief Display line numbers.
*/
ScriptEditor::LineNumberWidget::LineNumberWidget(ScriptEditor* editor)
    : QWidget(editor), scriptEditor(editor)
{
    QPalette p = palette();
    p.setColor(QPalette::Background, Qt::lightGray);
    setAutoFillBackground(true);
    setPalette(p);
}

QSize ScriptEditor::LineNumberWidget::sizeHint() const
{
    return QSize(scriptEditor->getLineNumberAreaWidth(), 0);
}

void ScriptEditor::LineNumberWidget::paintEvent(QPaintEvent* ev)
{
    scriptEditor->paintLineNumbers(ev);
}