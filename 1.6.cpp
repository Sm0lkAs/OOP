#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <windows.h>

using namespace std;

// Объявление функций для специализаций
template<typename T>
void merge(vector<T>& arr, int left, int mid, int right);

template<>
void merge<char*>(vector<char*>& arr, int left, int mid, int right);

// Функция для слияния двух половин
template <typename T>
void merge(vector<T>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<T> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        } else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Специализация для C-строк
template <>
void merge<char*>(vector<char*>& arr, int left, int mid, int right) 
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<char*> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) 
        {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) 
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Функция сортировки слиянием
template <typename T>
void mergeSort(vector<T>& arr, int left, int right) 
{
    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Функция для отображения массива
template <typename T>
void displayArray(const vector<T>& arr) 
{
    for (const auto& elem : arr) 
    {
        cout << elem << " ";
    }
    cout << endl;
}

// Специализация для C-строк
template <>
void displayArray<char*>(const vector<char*>& arr) 
{
    cout << "[ ";
    for (const auto& elem : arr) 
    {
        cout << elem << " ";
    }
    cout << "]" << endl;
    cout << endl;
}

// Функция для заполнения массива
template <typename T>
void fillArray(vector<T>& arr) 
{
    cout << "Введите " << arr.size() << " элементов:" << endl;
    for (auto& elem : arr) 
    {
        cin >> elem;
    }
    
}

// Специализация для C-строк
template <>
void fillArray<char*>(vector<char*>& arr) 
{
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    cin.ignore();
    
    cout << "Введите " << arr.size() << " строк:" << endl;
    for (auto& elem : arr) 
    {
        cin.getline(buffer, BUFFER_SIZE);
        elem = new char[strlen(buffer) + 1];
        strcpy(elem, buffer);
    }
}

int main() 
{
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int size, choice;
    cout << "Введите размер массива: ";
    cin >> size;
    
    cout << "Выберите тип данных:\n1 - int\n2 - double\n3 - char\n4 - C-строка\n";
    cin >> choice;

    switch(choice) 
    {
        case 1: 
        {
            vector<int> arr(size);
            fillArray(arr);
            mergeSort(arr, 0, size-1);
            displayArray(arr);
            break;
        }
        case 2: 
        {
            vector<double> arr(size);
            fillArray(arr);
            mergeSort(arr, 0, size-1);
            displayArray(arr);
            break;
        }
        case 3: 
        {
            vector<char> arr(size);
            fillArray(arr);
            mergeSort(arr, 0, size-1);
            displayArray(arr);
            break;
        }
        case 4: 
        {
            vector<char*> arr(size);
            fillArray(arr);
            mergeSort(arr, 0, size-1);
            displayArray(arr);
            
            // Освобождение памяти
            for (auto& elem : arr) 
            {
                delete[] elem;
            }
            break;
        }
        default:
            cout << "Неверный выбор!" << endl;
    }

    cin.ignore();
    cin.get();
    return 0;
}