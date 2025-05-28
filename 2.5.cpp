#include <iostream>
#include <unordered_map>

using namespace std;

const int MAX_SIZE = 100;  // Максимальный размер массивов

struct ArrayList {
    char A[MAX_SIZE];  // Массив значений
    int B[MAX_SIZE];   // Массив индексов
    int nz = -1;       // Индекс начала списка данных
    int ns = 0;        // Индекс начала свободных узлов
    int size = 0;      // Текущий размер списка

    ArrayList() {
        for (int i = 0; i < MAX_SIZE - 1; ++i) {
            B[i] = i + 1;
        }
        B[MAX_SIZE - 1] = -1;
    }

    void push_back(char value) {
        if (ns == -1) {
            cerr << "Список полон!" << endl;
            return;
        }

        int new_node = ns;
        ns = B[ns];

        A[new_node] = value;
        B[new_node] = -1;

        if (nz == -1) {
            nz = new_node;
        } else {
            int current = nz;
            while (B[current] != -1) {
                current = B[current];
            }
            B[current] = new_node;
        }
        size++;
    }

    int find(char value) {
        int current = nz;
        while (current != -1) {
            if (A[current] == value) return current;
            current = B[current];
        }
        return -1;
    }

    void print() {
        int current = nz;
        while (current != -1) {
            cout << A[current] << " ";
            current = B[current];
        }
        cout << endl;
    }

    char get_at_index(int index) {
        int current = nz;
        for (int i = 0; i < index && current != -1; ++i) {
            current = B[current];
        }
        return (current != -1) ? A[current] : '\0';
    }
};

ArrayList create_unique_list(const ArrayList& L1) {
    unordered_map<char, int> count;
    ArrayList L2;

    // Подсчет частот
    int current = L1.nz;
    while (current != -1) {
        count[L1.A[current]]++;
        current = L1.B[current];
    }

    current = L1.nz;
    while (current != -1) {
        if (count[L1.A[current]] == 1) {
            L2.push_back(L1.A[current]);
        }
        current = L1.B[current];
    }

    return L2;
}

int main() {
    ArrayList L1;
    L1.push_back('q');
    L1.push_back('w');
    L1.push_back('e');
    L1.push_back('q');
    L1.push_back('e');
    L1.push_back('t');
    L1.push_back('b');
    L1.push_back('f');

    cout << "L1: ";
    L1.print();

    ArrayList L2 = create_unique_list(L1);
    cout << "L2 (uniq): ";
    L2.print();

    cin.ignore();  // Игнорирование пустой строки
    cin.get();     // Для того, чтобы не закрывался консольный окно при запуске программ

    return 0;
}