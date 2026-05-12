#ifndef PROJECTOOP_SPELL_CHECKER_HIGHLIGHTER_H
#define PROJECTOOP_SPELL_CHECKER_HIGHLIGHTER_H

#include "spell_checker.h"

#include <QSyntaxHighlighter>
#include <QTextCharFormat>
#include <QRegularExpression>

class spell_checker_highlighter : public QSyntaxHighlighter {
public:
    spell_checker_highlighter(QTextDocument *doc, const spell_checker& spell_checker)
        : QSyntaxHighlighter(doc),  spell_checker(spell_checker){
        format.setUnderlineStyle(QTextCharFormat::SpellCheckUnderline);
        format.setUnderlineColor(Qt::red);
    }

    void highlightBlock(const QString &text) override {
        const QRegularExpression word_regex("\\b\\w+\\b");
        auto iterator = word_regex.globalMatch(text);

        while (iterator.hasNext()) {
            auto match = iterator.next();
            QString word = match.captured();

            if (!spell_checker.isCorrect(word.toStdString())) {
                setFormat(match.capturedStart(), match.capturedLength(), format);
            }
        }

    }

private:
    QTextCharFormat format;
    spell_checker spell_checker;
};

#endif //PROJECTOOP_SPELL_CHECKER_HIGHLIGHTER_H
