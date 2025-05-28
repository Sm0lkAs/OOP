#ifndef LETTERSET_H
#define LETTERSET_H

#include <cctype>
#include <iostream>
#include <string>

class LetterSet {
   private:
    // Хранение множества латинских букв: массив для букв a-z
    bool letters[26];

   public:
    // Конструкторы
    LetterSet();                            // Конструктор без параметров
    LetterSet(const std::string& str);      // Конструктор с параметром (инициализация по строке)
    LetterSet(const LetterSet& other);      // Конструктор копирования
    LetterSet(LetterSet&& other) noexcept;  // Конструктор перемещения

    // Деструктор
    ~LetterSet();

    // Операторы присваивания
    LetterSet& operator=(const LetterSet& other);
    LetterSet& operator=(LetterSet&& other) noexcept;

    // Объединение – оператор +
    LetterSet operator+(const LetterSet& other) const;
    // Пересечение – оператор *
    LetterSet operator*(const LetterSet& other) const;
    // Разность – оператор -
    LetterSet operator-(const LetterSet& other) const;

    // Добавление элемента во множество – оператор +=
    LetterSet& operator+=(char ch);
    // Удаление элемента из множества – оператор -=
    LetterSet& operator-=(char ch);

    // Перегрузка ввода/вывода
    friend std::ostream& operator<<(std::ostream& os, const LetterSet& set);
    friend std::istream& operator>>(std::istream& is, LetterSet& set);
};

#endif  // LETTERSET_H
