#include <iostream>
using namespace std;

struct Node {
    double data;
    Node* prev;
    Node* next;
    Node(double val) : data(val), prev(nullptr), next(nullptr) {}  // присвоение
};

int main() {
    int n;
    cin >> n;

    Node* head = nullptr;
    Node* tail = nullptr;

    for (int i = 0; i < n; ++i) {
        double x;
        cin >> x;
        Node* newNode = new Node(x);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    double sum = 0.0;
    Node* left = head;
    Node* right = tail;

    for (int i = 0; i < n; ++i) {
        sum += left->data * right->data;
        left = left->next;
        right = right->prev;
    }

    cout << sum << endl;

    Node* current = head;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    cin.ignore();  // Игнорирование пустой строки
    cin.get();     // Для того, чтобы не закрывался консольный окно при запуске программ

    return 0;
}