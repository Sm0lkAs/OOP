#ifndef OOP_4_1_HEADER_H
#define OOP_4_1_HEADER_H

#include <algorithm>
#include <iostream>
#include <stdexcept>

template <typename T>
class Vector {
   private:
    T* data;
    long long size;

   public:
    // Конструкторы и деструктор
    Vector();
    explicit Vector(long long size, const T& value = T());
    explicit Vector(long long size);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    ~Vector();

    // Операторы присваивания
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;

    // Методы
    void resize(long long new_size);
    int getSize() const;
    void fillRandom();
    void Print();

    // Перегрузка операторов
    T& operator[](long long index);
    const T& operator[](long long index) const;

    // Дружественные операторы ввода/вывода
    friend std::ostream& operator<<(
        std::ostream& os,
        const Vector<T>& vec)  // баг при использовании cout << a[i] выводит весь вектор и i элемент
    {
        for (long long i = 0; i < vec.size; ++i) {
            os << vec.data[i] << " ";
        }
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Vector& vec) {
        for (long long i = 0; i < vec.size; ++i) {
            is >> vec.data[i];
        }
        return is;
    }
};

template <>
void Vector<int>::fillRandom();
template <>
void Vector<double>::fillRandom();
template <>
void Vector<std::string>::fillRandom();

template <>
void Vector<int>::Print();
template <>
void Vector<double>::Print();
template <>
void Vector<std::string>::Print();

template class Vector<int>;
template class Vector<double>;
template class Vector<bool>;
template class Vector<std::string>;

#endif  // OOP_4_1_HEADER_H