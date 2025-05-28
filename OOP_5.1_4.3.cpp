#include <cctype>
#include <iostream>
#include <string>

bool areWordsEqual(const std::string& word1, const std::string& word2) {
    int letters[256] = {0};

    for (char ch : word1) {
        letters[tolower(ch)]++;
    }

    for (char ch : word2) {
        if (letters[tolower(ch)] == 0) {
            return false;
        }
        letters[tolower(ch)]--;
    }
    return true;
}

void extractMatchingWords(const std::string& text) {
    size_t start = 0;
    size_t end = text.find_first_of(" .,;!?()-");
    std::string firstWord;

    while (end != std::string::npos) {
        std::string word = text.substr(start, end - start);
        if (word.empty()) {
            start = end + 1;
            end = text.find_first_of(" .,;!?()-", start);
            continue;
        }

        if (firstWord.empty()) {
            firstWord = word;
        } else if (areWordsEqual(firstWord, word)) {
            std::cout << word << " ";
        }

        start = end + 1;
        end = text.find_first_of(" .,;!?()-", start);
    }

    std::string lastWord = text.substr(start);
    if (areWordsEqual(firstWord, lastWord)) {
        std::cout << lastWord << " ";
    }

    std::cout << std::endl;
}

int main() {
    std::string text = "listen silent enlist test";
    extractMatchingWords(text);

    std::cin.ignore();
    std::cin.get();
    return 0;
}
