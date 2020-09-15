#pragma once

#include <QSyntaxHighlighter>
#include <QTextDocument>
#include <QVector>
#include <QRegularExpression>
#include <QTextCharFormat>

class Highlighter : public QSyntaxHighlighter {
public:
    Highlighter(QTextDocument* parent = nullptr);

protected:
    void highlightBlock(QString const& text) override;

private:
    Q_OBJECT

    struct HighlightingRule {
        QRegularExpression pattern;
        QTextCharFormat format;
    };
    
    QVector<HighlightingRule> highlightingRules;

    QRegularExpression commentStartExpression;
    QRegularExpression commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat classFormat;
    QTextCharFormat singleLineCommentFormat;
    QTextCharFormat multiLineCommentFormat;
    QTextCharFormat quotationFormat;
    QTextCharFormat functionFormat;
};