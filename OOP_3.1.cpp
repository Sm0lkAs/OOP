#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void merge_files(const string& file1, const string& file2, const string& output) {
    ifstream f(file1);
    ifstream g(file2);
    ofstream out(output);

    if (!f.is_open() || !g.is_open() || !out.is_open()) {
        cerr << "Can not read the file!" << endl;
        return;
    }

    double num_f, num_g;
    bool has_f = !!(f >> num_f);
    bool has_g = !!(g >> num_g);

    while (has_f && has_g) {
        if (num_f <= num_g) {
            out << num_f << '\n';
            has_f = !!(f >> num_f);
        } else {
            out << num_g << '\n';
            has_g = !!(g >> num_g);
        }
    }

    while (has_f) {
        out << num_f << '\n';
        has_f = !!(f >> num_f);
    }

    while (has_g) {
        out << num_g << '\n';
        has_g = !!(g >> num_g);
    }

    f.close();
    g.close();
    out.close();
}

int main() {
    merge_files("f.txt", "g.txt", "result.txt");
    cout << "Files merged successfully!" << endl;
    cin.ignore();
    cin.get();
    return 0;
}