#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Fill_File_1();

void Fill_File_2();

void print_binary_file(const string& filename) {
    ifstream file(filename, ios::binary);

    if (!file.is_open()) {
        cerr << "can not read file:  " << filename << "!" << endl;
        return;
    }

    cout << "Date in file " << filename << ":\n";

    double number;
    while (file.read(reinterpret_cast<char*>(&number), sizeof(double))) {
        if (file.gcount() == sizeof(double)) {
            cout << number << " ";
        } else {
            break;
        }
    }

    cout << "\n\n";
    file.close();
}

void merge_binary_files(const string& file1, const string& file2, const string& output) {
    ifstream f(file1, ios::binary);
    ifstream g(file2, ios::binary);
    ofstream out(output, ios::binary);

    if (!f.is_open() || !g.is_open() || !out.is_open()) {
        cerr << "Can not open the file!" << endl;
        return;
    }

    double num_f, num_g;
    bool has_f = false, has_g = false;

    f.read(reinterpret_cast<char*>(&num_f), sizeof(num_f));
    has_f = (f.gcount() == sizeof(num_f));  // gcount() возвращает количество байт, успешно
                                            // прочитанных последней операцией чтения

    g.read(reinterpret_cast<char*>(&num_g), sizeof(num_g));
    has_g = (g.gcount() == sizeof(num_g));

    while (has_f && has_g) {
        if (num_f <= num_g) {
            out.write(reinterpret_cast<const char*>(&num_f), sizeof(num_f));

            f.read(reinterpret_cast<char*>(&num_f), sizeof(num_f));
            has_f = (f.gcount() == sizeof(num_f));
        } else {
            out.write(reinterpret_cast<const char*>(&num_g), sizeof(num_g));

            g.read(reinterpret_cast<char*>(&num_g), sizeof(num_g));
            has_g = (g.gcount() == sizeof(num_g));
        }
    }

    while (has_f) {
        out.write(reinterpret_cast<const char*>(&num_f), sizeof(num_f));
        f.read(reinterpret_cast<char*>(&num_f), sizeof(num_f));
        has_f = (f.gcount() == sizeof(num_f));
    }

    while (has_g) {
        out.write(reinterpret_cast<const char*>(&num_g), sizeof(num_g));
        g.read(reinterpret_cast<char*>(&num_g), sizeof(num_g));
        has_g = (g.gcount() == sizeof(num_g));
    }

    f.close();
    g.close();
    out.close();
}

int main() {
    srand(time(nullptr));

    Fill_File_1();
    Fill_File_2();

    merge_binary_files("f.bin", "g.bin", "result.bin");
    cout << "Binary files merged successfully!" << endl;

    print_binary_file("f.bin");
    print_binary_file("g.bin");

    print_binary_file("result.bin");

    cin.ignore();
    cin.get();
    return 0;
}

void Fill_File_1() {
    std::vector<double> data_f;

    for (int i = 0; i < rand() % 10; i++) data_f.push_back(-5 + rand() % 10 + (rand() % 10) / 10.0);
    sort(data_f.begin(), data_f.end());
    std::ofstream file("f.bin", std::ios::binary);
    file.write(reinterpret_cast<const char*>(data_f.data()), data_f.size() * sizeof(double));
    file.close();
}

void Fill_File_2() {
    std::vector<double> data_f;

    for (int i = 0; i < rand() % 10; i++) data_f.push_back(-5 + rand() % 10 + (rand() % 10) / 10.0);
    sort(data_f.begin(), data_f.end());
    std::ofstream file("g.bin", std::ios::binary);
    file.write(reinterpret_cast<const char*>(data_f.data()), data_f.size() * sizeof(double));
    file.close();
}