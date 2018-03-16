/*
** papyrushighlighter.cpp
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
    // TODO: Replace if/when parser available. These are all scripts.
    keywords << "\\bActor\\b";

    for (auto& keyword : keywords) {
        rule.pattern = QRegularExpression(keyword, QRegularExpression::CaseInsensitiveOption);
        rule.format = keywordFormat;
        rules.append(rule);
    }

    // Number literals.
    QBrush numLiteralBrush(QColor(181, 106, 168));

    numberLiteralFormat.setForeground(numLiteralBrush);
    rule.pattern = QRegularExpression("\\b[+-]?[0-9]+(?:.[0-9]+)?(?:[eE][+-]?[0-9]+)?\\b", QRegularExpression::MultilineOption); //\b[+-]?[0-9]+(?:.[0-9]+)?(?:[eE][+-]?[0-9]+)?\b //\\b(([+-]?\\d*(\\.|,)?\\d+([eE][+-]?\\d+)?)(?![A-Za-z0-9.]))
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