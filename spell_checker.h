#ifndef PROJECTOOP_SPELL_CHECKER_H
#define PROJECTOOP_SPELL_CHECKER_H

#include <string>
#include <set>
#include <QFile>
#include <QTextStream>


class spell_checker {
public:
    spell_checker() = default;

    void load_dictionary() {
        QFile file("data/words.txt");

        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            return;
        }

        QTextStream in(&file);

        while (!in.atEnd()) {
            QString word = in.readLine();
            dictionary.insert(word.toStdString());
        }
    }

    static std::string normalize_word(const std::string& word) {
        std::string result;
        for (auto ch : word) {
            if (std::isalpha(static_cast<unsigned char>(ch))) {
                result += std::tolower(ch);
            }
        }

        return result;
    }

    [[nodiscard]] bool isCorrect(const std::string& word) const {
        auto normalized = normalize_word(word);

        if (normalized.empty()) {
            return true;
        }

        return dictionary.contains(normalized);
    }

    [[nodiscard]] std::vector<std::string> suggestions(const std::string& word) const {
        const std::string normalized = normalize_word(word);

        if (normalized.empty()) {
            return {};
        }

        std::vector<std::string> result;

        for (const auto &w : dictionary) {
            if (w[0] == normalized[0] && w[1] == normalized[1] && w[2] == normalized[2]) {
                result.push_back(w);
            }

            if (result.size() >= 5) {
                break;
            }
        }

        return result;
    }
private:
    std::set<std::string> dictionary;
};


#endif //PROJECTOOP_SPELL_CHECKER_H
