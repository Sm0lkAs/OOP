#include <iostream>
#include <unordered_map>
using namespace std;

template <typename T>
class DoubleList {
   public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };
    Node* head;
    Node* tail;
    int size;

   public:
    DoubleList() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    ~DoubleList() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
        tail = nullptr;
    }

    void push_back(T value) {
        Node* newNode = new Node();
        newNode->data = value;
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void delete_back() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }
        if (head == tail) {
            delete head;
            head = tail = nullptr;
        } else {
            Node* end = tail->prev;
            delete tail;
            tail = end;
            tail->next = nullptr;
        }
        size--;
    }

    bool Find(T value) {
        for (Node* current = head; current != nullptr; current = current->next) {
            if (current->data == value) return true;
        }
        return false;
    }

    void print() {
        Node* current = head;
        if (head == nullptr) {
            cout << "List is empty" << endl;
            return;
        }
        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void Delete_List() {
        while (head != nullptr) {
            Node* next = head->next;
            delete head;
            head = next;
        }
        head = tail = nullptr;
        size = 0;
    }

    DoubleList<T> create_unique_list() {
        unordered_map<T, int> freq;
        for (Node* current = head; current; current = current->next) freq[current->data]++;

        DoubleList<T> L2;
        for (Node* current = head; current; current = current->next)
            if (freq[current->data] == 1) L2.push_back(current->data);

        return L2;
    }

    Node* get_head() { return head; }
    Node* get_tail() { return tail; }
    int get_size() { return size; }
};

int main() {
    int n;
    cout << "Enter n: ";
    cin >> n;

    DoubleList<double> numbers;
    cout << "Enter " << n << " numbers: ";

    for (int i = 0; i < n; i++) {
        double num;
        cin >> num;
        numbers.push_back(num);
    }

    cout << "List: ";
    numbers.print();

    // Вычисление суммы по формуле
    double result = 0.0;
    auto left = numbers.get_head();
    auto right = numbers.get_tail();

    for (int i = 0; i < n; i++) {
        result += left->data * right->data;
        left = left->next;
        right = right->prev;
    }

    cout << "Result: " << result << endl;

    cin.ignore();
    cin.get();
    return 0;
}