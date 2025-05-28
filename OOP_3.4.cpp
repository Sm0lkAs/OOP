#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

const int CountOfStudents = 5;

#pragma pack(push, 1)
struct Student {
    string fio;   // ФИО
    int age;      // Возраст
    char gender;  // Пол ('M' или 'F')
    int course;   // Курс
    float gpa;    // Средний балл
};

#pragma pack(pop)
void createTestFile(const string& filename) {
    ofstream out_file(filename);
    if (!out_file) {
        cerr << "Error in creating file!" << endl;
        return;
    }

    Student students[] = {{"Ivanov Ivan", 19, 'M', 1, 4.5},
                          {"Pozornik Opushen", 17, 'F', 1, 4.8},
                          {"Mikhail Borovikov", 20, 'M', 2, 4.2},
                          {"Cidiriv Ilya", 18, 'F', 2, 4.9},
                          {"Smirnov Alex", 16, 'M', 3, 3.7}};

    for (const auto& s : students) {
        out_file << s.fio << ' ' << s.age << ' ' << s.gender << ' ' << s.course << ' ' << s.gpa
                 << "\n";
    }

    out_file.close();
    cout << "Test file created: \"" << filename << "\"" << endl;
}

bool isInteger(const string& s) {
    if (s.empty()) return false;

    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}

void readFile(string filename) {
    ifstream dateFile(filename);

    Student studentsFromFile[CountOfStudents];

    int npoz = 0;

    while (npoz < CountOfStudents) {
        string fio;
        int age;
        char gender;
        int course;
        double gpa;

        string name;
        dateFile >> name;
        while (!isInteger(name)) {
            fio += name + " ";
            dateFile >> name;
        }
        if (!fio.empty()) fio.pop_back();  // Убрать последний пробел

        age = stoi(name);

        dateFile >> name;

        gender = name[0];

        dateFile >> name;

        course = stoi(name);

        dateFile >> name;

        gpa = stof(name);

        studentsFromFile[npoz].fio = fio;
        studentsFromFile[npoz].age = age;
        studentsFromFile[npoz].gender = gender;
        studentsFromFile[npoz].course = course;
        studentsFromFile[npoz].gpa = gpa;

        npoz++;
    }

    map<int, Student> youngStudents;

    for (const auto& student : studentsFromFile) {
        auto it = youngStudents.find(student.course);

        if (it == youngStudents.end()) {  // если курс встречается впервые
            youngStudents[student.course] = student;
        } else {  // сравниваем с текущим минимальным возрастом
            if (student.age < it->second.age) {
                youngStudents[student.course] = student;
            }
        }
    }

    ofstream out_file("outputfile.txt");
    for (const auto& pair : youngStudents) {
        out_file << pair.second.fio << " | Курс: " << pair.first
                 << " | Возраст: " << pair.second.age << endl;
    }
    dateFile.close();
    out_file.close();
    cout << "We find! All in \"outputfile.txt\"" << endl;
}

int main() {
    createTestFile("students.txt");

    Student studentsFromFile[5];

    readFile("students.txt");

    cin.ignore();
    cin.get();
    return 0;
}