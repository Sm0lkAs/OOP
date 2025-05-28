#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "OOP_4.1.header.h"

// Макросы для цветов
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"

// Конструктор по умолчанию
template <typename T>
Vector<T>::Vector() : data(nullptr), size(0){};

template <typename T>
Vector<T>::Vector(long long size, const T& value) : size(size), data(new T[size]) {
    for (long long i = 0; i < size; ++i) {
        data[i] = value;
    }
}

// Конструктор с параметром
template <typename T>
Vector<T>::Vector(long long size) {
    this->size = size;

    data = new T[size]();
}

// Конструктор копирования
template <typename T>
Vector<T>::Vector(const Vector<T>& other) : size(other.size) {
    data = new T[size];
    for (int i = 0; i < size; ++i) {
        data[i] = other.data[i];
    }
}

// Конструктор перемещения
template <typename T>
Vector<T>::Vector(Vector&& other) noexcept {
    this->size = other.size;
    this->data = other.data;
    other.size = 0;
    other.data = nullptr;
}

// Деструктор
template <typename T>
Vector<T>::~Vector() {
    delete[] data;
    data = nullptr;
}

// Оператор присваивания копированием
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        for (int i = 0; i < this->size; i++) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

// Оператор присваивания перемещением
template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        this->data = other.data;
        this->size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    return *this;
}

// Изменение размерности
template <typename T>
void Vector<T>::resize(long long new_size) {
    T* new_data = new T[new_size];
    for (int i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    for (int i = size; i < new_size; i++) {
        new_data[i] = T();
    }
    delete[] this->data;
    this->data = new_data;
    size = new_size;
}

// Получение размера
template <typename T>
int Vector<T>::getSize() const {
    return size;
}

// Заполнение случайными значениями
// Специализация для int
template <>
void Vector<int>::fillRandom() {
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        data[i] = rand() % 100;
    }
}

// Специализация для double
template <>
void Vector<double>::fillRandom() {
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        data[i] = (rand() % 1000) / 10.0;
    }
}

// Специализация для string
template <>
void Vector<std::string>::fillRandom() {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(nullptr));
    for (int i = 0; i < size; ++i) {
        std::string str;
        for (int j = 0; j < 5; ++j) {
            str += charset[rand() % 26];
        }
        data[i] = str;
    }
}

// Вывод в консоль
//  Специализация для int
template <>
void Vector<int>::Print() {
    std::cout << GREEN;
    std::cout << "Vector : ";
    for (int i = 0; i < size; i++) std::cout << data[i] << ' ';
    std::cout << RESET << std::endl;
}

// Специализация для double
template <>
void Vector<double>::Print() {
    std::cout << GREEN;
    std::cout << "Vector : ";
    for (int i = 0; i < size; i++) std::cout << data[i] << ' ';
    std::cout << RESET << std::endl;
}

// Специализация для string
template <>
void Vector<std::string>::Print() {
    std::cout << GREEN;
    std::cout << "Vector : ";
    for (int i = 0; i < size; i++) std::cout << data[i];
    std::cout << RESET << std::endl;
}

// Оператор индексирования (L-value)
template <typename T>
T& Vector<T>::operator[](long long index) {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");

    return data[index];
}

// Оператор индексирования (R-value)
template <typename T>
const T& Vector<T>::operator[](long long index) const {
    if (index < 0 || index >= size) throw std::out_of_range("Index out of range");

    return data[index];
}
