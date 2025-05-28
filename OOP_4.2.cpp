#include <iostream>
#include <map>
#include <stdexcept>  // Для std::logic_error
#include <utility>

template <typename T>
class LinearList {
   private:
    struct Node {
        T data;
        Node* next;

        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

   public:
    // Конструкторы
    LinearList() : head(nullptr), tail(nullptr), size(0) {}
    LinearList(const T& value) : head(new Node(value)), tail(head), size(1) {}

    // Деструктор
    ~LinearList() { clear(); }

    // Конструктор копирования
    LinearList(const LinearList& other) : head(nullptr), tail(nullptr), size(0) {
        Node* current = other.head;
        while (current) {
            add(current->data);
            current = current->next;
        }
    }

    // Оператор присваивания копированием
    LinearList& operator=(const LinearList& other) {
        if (this != &other) {
            clear();
            head = std::exchange(other.head, nullptr);
            tail = std::exchange(other.tail, nullptr);
            size = std::exchange(other.size, 0);
        }
        return *this;
    }

    // Конструктор перемещения
    LinearList(LinearList&& other) noexcept : head(other.head), tail(other.tail), size(other.size) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0;
    }

    // Оператор присваивания перемещением
    LinearList& operator=(LinearList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            tail = other.tail;
            size = other.size;
            other.head = nullptr;
            other.tail = nullptr;
            other.size = 0;
        }
        return *this;
    }

    // Инициализация первого элемента
    void initFirstElement(const T& value) {
        if (!head) {
            head = new Node(value);
            tail = head;
            size = 1;
        } else {
            throw std::logic_error("List is not empty");
        }
    }

    // Добавление элемента в конец
    void add(const T& value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        size++;
    }

    // Удаление элемента по ключу
    bool remove(const T& key) {
        if (!head) return false;

        Node* prev = nullptr;
        Node* current = head;

        while (current && current->data != key) {
            prev = current;
            current = current->next;
        }

        if (!current) return false;

        if (!prev) {
            head = current->next;
            if (!head) tail = nullptr;
        } else {
            prev->next = current->next;
            if (current == tail) tail = prev;
        }

        delete current;
        size--;
        return true;
    }

    // Поиск элемента по ключу
    bool find(const T& key) const {
        Node* current = head;
        while (current) {
            if (current->data == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    // Вывод элементов
    void print() const {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << "\n";
    }

    // Очистка списка
    void clear() noexcept {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        size = 0;
    }
};

int main() {
    LinearList<char> L1;

    std::string input = "aabbcdeffg";
    for (char ch : input) {
        L1.add(ch);
    }

    std::cout << "L1: ";
    L1.print();

    std::map<char, int> freq;
    for (char ch : input) {
        freq[ch]++;
    }

    LinearList<char> L2;
    for (char ch : input) {
        if (freq[ch] == 1) {
            L2.add(ch);
        }
    }

    std::cout << "L2 (unique elements): ";
    L2.print();

    std::cin.ignore();
    std::cin.get();

    return 0;
}