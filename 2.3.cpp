#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tuple>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Для работы с кодовыми страницами
#include <locale>

using std::cout;
using std::endl;
using std::left;
using std::right;
using std::abs;


using namespace std;

struct Date 
{
    int day;
    int month;
    int year;

    bool operator>(const Date& other) const 
    {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }

    bool operator==(const Date& other) const 
    {
        return day == other.day && month == other.month && year == other.year;
    }
};

struct Student 
{
    string fullName;
    Date birthDate;
    int course;
    float gpa;
    Student* next;

    Student(const string& name, const Date& date, int c, float g, Student* n = nullptr)
        : fullName(name), birthDate(date), course(c), gpa(g), next(n) {}
};

class LinkedList 
{
private:
    Student* head;

    static string extractSurname(const string& fullName) 
    {
        size_t spacePos = fullName.find(' ');
        return (spacePos != string::npos) ? fullName.substr(0, spacePos) : fullName;
    }

public:
    LinkedList() : head(nullptr) {}

    ~LinkedList() 
    {
        Student* current = head;
        while (current) 
        {
            Student* next = current->next;
            delete current;
            current = next;
        }
    }

    void addStudent(const string& name, const Date& date, int course, float gpa) 
    {
        Student* newStudent = new Student(name, date, course, gpa, nullptr);
        string newSurname = extractSurname(name);

        if (!head || extractSurname(head->fullName) > newSurname) 
        {
            newStudent->next = head;
            head = newStudent;
            return;
        }

        Student* current = head;
        while (current->next && extractSurname(current->next->fullName) <= newSurname) 
            current = current->next;

        newStudent->next = current->next;
        current->next = newStudent;
    }

    LinkedList findAndRemoveYoungestPerCourse() 
    {
        map<int, Date> maxDates;
        Student* current = head;

        while (current) 
        {
            int course = current->course;
            if (!maxDates.count(course) || current->birthDate > maxDates[course])
                maxDates[course] = current->birthDate;
            current = current->next;
        }

        vector<tuple<string, Date, int, float>> studentsData;
        current = head;
        Student* prev = nullptr;

        while (current) 
        {
            int course = current->course;
            if (current->birthDate == maxDates[course]) 
            {
                studentsData.emplace_back(current->fullName, current->birthDate, course, current->gpa);
                Student* toDelete = current;
                (prev ? prev->next : head) = current->next;
                current = current->next;
                delete toDelete;
            } else 
            {
                prev = current;
                current = current->next;
            }
        }

        LinkedList newList;
        for (const auto& data : studentsData) 
        {
            newList.addStudent(get<0>(data), get<1>(data), get<2>(data), get<3>(data));
        }

        return newList;
    }

    void print() const 
    {
        Student* current = head;
        while (current) 
        {
            cout << current->fullName << " (Курс: " << current->course 
                 << ", Рождён: " << current->birthDate.day << "."
                 << current->birthDate.month << "." << current->birthDate.year << ")\n";
            current = current->next;
        }
        cout << endl;
    }
};

int main() 
{
    SetConsoleOutputCP(65001); // Устанавливаем кодовую страницу для вывода
    SetConsoleCP(65001);       // Устанавливаем кодовую страницу для ввода
    setlocale(LC_ALL, "ru_RU.UTF-8");

    LinkedList list;

    list.addStudent("Терехов Даниил Александрович", Date{30, 6, 2006}, 1, 4.8);
    list.addStudent("Иванов Иван Иванович", Date{15, 5, 2004}, 2, 4.5);
    list.addStudent("Сидорова Анна Михайловна", Date{20, 1, 2005}, 1, 4.9);
    list.addStudent("Демидов Дмитрий Александрович", Date{7, 7, 2003}, 2, 4.7);

    cout << "Исходный список студентов:\n";
    list.print();

    LinkedList youngestList = list.findAndRemoveYoungestPerCourse();

    cout << "Список после удаления самых младших:\n";
    list.print();

    cout << "Самые младшие на курсах:\n";
    youngestList.print();

    cin.ignore(); // Игнорирование пустой строки
    cin.get();    // Для того, чтобы не закрывался консольный окно при запуске программ
}