#include "OOP_4.4.h"

// Конструктор без параметров
LetterSet::LetterSet() {
    for (int i = 0; i < 26; i++) {
        letters[i] = false;
    }
}

// Конструктор с параметром
LetterSet::LetterSet(const std::string& str) : LetterSet() {
    for (char ch : str) {
        if (std::isalpha(ch)) {
            ch = std::tolower(ch);
            letters[ch - 'a'] = true;
        }
    }
}

// Конструктор копирования
LetterSet::LetterSet(const LetterSet& other) {
    for (int i = 0; i < 26; i++) {
        letters[i] = other.letters[i];
    }
}

// Конструктор перемещения
LetterSet::LetterSet(LetterSet&& other) noexcept {
    for (int i = 0; i < 26; i++) {
        letters[i] = other.letters[i];
        other.letters[i] = false;
    }
}

// Деструктор
LetterSet::~LetterSet() {}

// Оператор присваивания копированием
LetterSet& LetterSet::operator=(const LetterSet& other) {
    if (this != &other) {
        for (int i = 0; i < 26; i++) {
            letters[i] = other.letters[i];
        }
    }
    return *this;
}

// Оператор присваивания перемещением
LetterSet& LetterSet::operator=(LetterSet&& other) noexcept {
    if (this != &other) {
        for (int i = 0; i < 26; i++) {
            letters[i] = other.letters[i];
            other.letters[i] = false;
        }
    }
    return *this;
}

// Перегруженный оператор + (объединение двух множеств)
LetterSet LetterSet::operator+(const LetterSet& other) const {
    LetterSet result;
    for (int i = 0; i < 26; i++) {
        result.letters[i] = this->letters[i] || other.letters[i];
    }
    return result;
}

// Перегруженный оператор * (пересечение двух множеств)
LetterSet LetterSet::operator*(const LetterSet& other) const {
    LetterSet result;
    for (int i = 0; i < 26; i++) {
        result.letters[i] = this->letters[i] && other.letters[i];
    }
    return result;
}

// Перегруженный оператор - (разность двух множеств: буквы, присутствующие в этом, но отсутствующие
// в other)
LetterSet LetterSet::operator-(const LetterSet& other) const {
    LetterSet result;
    for (int i = 0; i < 26; i++) {
        result.letters[i] = this->letters[i] && !other.letters[i];
    }
    return result;
}

// Перегруженный оператор += (добавление буквы в множество)
LetterSet& LetterSet::operator+=(char ch) {
    if (std::isalpha(ch)) {
        ch = std::tolower(ch);
        letters[ch - 'a'] = true;
    }
    return *this;
}

// Перегруженный оператор -= (удаление буквы из множества)
LetterSet& LetterSet::operator-=(char ch) {
    if (std::isalpha(ch)) {
        ch = std::tolower(ch);
        letters[ch - 'a'] = false;
    }
    return *this;
}

// Перегруженный оператор вывода
std::ostream& operator<<(std::ostream& os, const LetterSet& set) {
    for (int i = 0; i < 26; i++) {
        if (set.letters[i]) {
            os << static_cast<char>('a' + i) << " ";
        }
    }
    return os;
}

// Перегруженный оператор ввода
std::istream& operator>>(std::istream& is, LetterSet& set) {
    std::string input;
    is >> input;
    // Очистим множество
    for (int i = 0; i < 26; i++) {
        set.letters[i] = false;
    }
    for (char ch : input) {
        if (std::isalpha(ch)) {
            ch = std::tolower(ch);
            set.letters[ch - 'a'] = true;
        }
    }
    return is;
}
