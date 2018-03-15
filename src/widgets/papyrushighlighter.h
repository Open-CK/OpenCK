#ifndef PAPYRUSHIGHLIGHTER_H
#define PAPYRUSHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QRegularExpression>

class PapyrusHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    PapyrusHighlighter(QTextDocument* parent = Q_NULLPTR);

protected:
    virtual void highlightBlock(const QString& text) override;

private:
    struct HighlightRule
    {
        QRegularExpression pattern;
        QTextCharFormat format;
    };

    QVector<HighlightRule> rules;

    QTextCharFormat keywordFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat stringLiteralFormat;
    QTextCharFormat numberLiteralFormat;
};

#endif