/*
** scripteditor.h
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

#ifndef SCRIPTEDITOR_H
#define SCRIPTEDITOR_H

#include <QPlainTextEdit>

class QSyntaxHighlighter;
class ScriptEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    ScriptEditor(QWidget* parent = Q_NULLPTR);
    ScriptEditor(const ScriptEditor&) = default;
    ScriptEditor& operator=(const ScriptEditor&) = default;
    ~ScriptEditor() = default;

protected:
    virtual void resizeEvent(QResizeEvent* ev) override;
    virtual void keyPressEvent(QKeyEvent* ev) override;

    virtual void wheelEvent(QWheelEvent* ev) override;

private slots:
    void on_blockCountChanged(int);
    void on_updateRequest(const QRect& rect, int dy);

private:
    class LineNumberWidget : public QWidget
    {
    public:
        LineNumberWidget(ScriptEditor* editor);

        QSize sizeHint() const;
    protected:
        void paintEvent(QPaintEvent* ev);

    private:
        ScriptEditor* scriptEditor{ nullptr };
    };

    // Line numbering.
    LineNumberWidget* lineNumberWidget{ nullptr };
    void paintLineNumbers(QPaintEvent* ev);
    int getLineNumberAreaWidth() const;
    static const quint32 LINENUMBER_PADDING = 5;

    // Highlighter.
    QSyntaxHighlighter* syntaxHighlighter{ nullptr };

    void executeGoToLine();
};

#endif