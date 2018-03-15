#include <widgets/papyrushighlighter.h>

PapyrusHighlighter::PapyrusHighlighter(QTextDocument* parent)
    : QSyntaxHighlighter(parent)
{
    HighlightRule rule;

    // Keywords
    keywordFormat.setForeground(Qt::darkBlue);
    keywordFormat.setFontWeight(QFont::Bold);

    QStringList keywords;
    keywords << "\\bScriptName\\b" << "\\bExtends\\b" << "\\bFunction\\b" << "\\bEndFunction\\b" << "\\bAuto\\b" << "\\bProperty\\b" << "\\bReturn\\b" << "\\bEvent\\b" << "\\bEndEvent\\b";

    // Types
    keywords << "\\bFloat\\b" << "\\bInt\\b" << "\\bString\\b" << "\\bGlobalVariable\\b";

    // Statements
    keywords << "\\bIf\\b" << "\\bElse\\b" << "\\bElseIf\\b" << "\\bEndIf\\b" << "\\bWhile\\b" << "\\bEndWhile\\b";

    // Classes
    keywords << "\\bActor\\b";

    for (auto& keyword : keywords) {
        rule.pattern = QRegularExpression(keyword, QRegularExpression::CaseInsensitiveOption);
        rule.format = keywordFormat;
        rules.append(rule);
    }

    // Number literals.
    QBrush numLiteralBrush(QColor(181, 106, 168));
    numberLiteralFormat.setForeground(numLiteralBrush);
    rule.pattern = QRegularExpression("\\b(([+-]?\\d*(\\.|,)?\\d+([eE][+-]?\\d+)?)(?![A-Za-z0-9.]))");

    rule.format = numberLiteralFormat;
    rules.append(rule);

    // String literals.
    stringLiteralFormat.setForeground(Qt::darkRed);
    rule.pattern = QRegularExpression("\".*\"");
    rule.format = stringLiteralFormat;
    rules.append(rule);

    // Commenting
    commentFormat.setForeground(Qt::darkGreen);
    rule.pattern = QRegularExpression(";[^\n]*");
    rule.format = commentFormat;
    rules.append(rule);
}

void PapyrusHighlighter::highlightBlock(const QString& text)
{
    for (auto& rule : rules) {
        QRegularExpressionMatchIterator it = rule.pattern.globalMatch(text);
        while (it.hasNext()) {
            QRegularExpressionMatch match = it.next();
            setFormat(match.capturedStart(), match.capturedLength(), rule.format);
        }
    }
}