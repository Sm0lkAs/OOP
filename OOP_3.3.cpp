#include <fstream>
#include <iostream>
#include <map>
#include <string>

using namespace std;

#pragma pack(push, 1)
struct Student {
    char fio[100];  // ФИО (фиксированный размер для записи)
    int age;        // Возраст
    char gender;    // Пол ('M' или 'F')
    int course;     // Курс
    float gpa;      // Средний балл
};
#pragma pack(pop)

void createTestFile(const string& filename) {
    ofstream out_file(filename, ios::binary);
    if (!out_file) {
        cerr << "Error in creating file!" << endl;
        return;
    }

    Student students[] = {{"Ivanov Ivan Ivanovich", 19, 'M', 1, 4.5},
                          {"Pozornik Opushen", 17, 'F', 1, 4.8},
                          {"Сидоров Петр Михайлович", 20, 'M', 2, 4.2},
                          {"Козлова Елена Викторовна", 18, 'F', 2, 4.9},
                          {"Smirnov Alex", 16, 'M', 3, 3.7}};

    for (const auto& s : students) {
        out_file.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }

    out_file.close();
    cout << "Test file created: " << filename << endl;
}

void processStudents(const string& input_path, const string& output_path) {
    ifstream in_file(input_path, ios::binary);
    if (!in_file) {
        cerr << "Error opening input file: " << input_path << endl;
        return;
    }

    map<int, Student> min_age_students;
    Student student;

    while (in_file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        auto it = min_age_students.find(student.course);
        if (it == min_age_students.end() || student.age < it->second.age) {
            min_age_students[student.course] = student;
        }
    }

    in_file.close();

    ofstream out_file(output_path, ios::binary);
    if (!out_file) {
        cerr << "Error creating output file: " << output_path << endl;
        return;
    }

    for (const auto& [course, student] : min_age_students) {
        out_file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
    }

    out_file.close();
}

int main() {
    createTestFile("students.bin");

    processStudents("students.bin", "youngest.bin");

    cout << "Results saved to: youngest.bin" << endl;

    std::cin.ignore();
    std::cin.get();
    return 0;
}