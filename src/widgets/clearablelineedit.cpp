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