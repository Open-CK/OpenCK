#include <widgets/scripteditor.h>
#include <QPainter>
#include <QTextBlock>

ScriptEditor::ScriptEditor(QWidget* parent)
    : QPlainTextEdit(parent)
{
    lineNumberWidget = new LineNumberWidget(this);

    on_blockCountChanged(0);
    connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(on_blockCountChanged(int)));
    connect(this, SIGNAL(updateRequest(const QRect&, int)), this, SLOT(on_updateRequest(const QRect&, int)));
}

ScriptEditor::LineNumberWidget::LineNumberWidget(ScriptEditor* editor) 
    : QWidget(editor), scriptEditor(editor)
{
}

void ScriptEditor::resizeEvent(QResizeEvent* ev)
{
    QPlainTextEdit::resizeEvent(ev);

    QRect contentBounds = contentsRect();
    lineNumberWidget->setGeometry(QRect(contentBounds.left(), contentBounds.top(), getLineNumberAreaWidth(), contentBounds.height()));
}

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

QSize ScriptEditor::LineNumberWidget::sizeHint() const
{
    return QSize(scriptEditor->getLineNumberAreaWidth(), 0);
}

void ScriptEditor::LineNumberWidget::paintEvent(QPaintEvent* ev)
{
    scriptEditor->paintLineNumbers(ev);
}