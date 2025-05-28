#include <iostream>
#include <climits>
#include <clocale>
#include <windows.h> // Для SetConsoleOutputCP


using namespace std;

void bubbleSort(int arr[], int size);
void cin_array(int arr[], int size);
void cout_array(int arr[], int size);
int& link(int arr[], int size, int min, int& poz);
int& link_bad(int arr[], int arr_2[], int size, int& min);

int main()
{
    SetConsoleOutputCP(65001); // Устанавливаем кодовую страницу для вывода
    SetConsoleCP(65001);       // Устанавливаем кодовую страницу для ввода
    setlocale(LC_ALL, "ru_RU.UTF-8");


    int poz;
    int n;
    cout << "Введите размер массива: \n";
    cin >> n;

    int* arr = new int[n];
    int* arr_2 = new int[n];

    cin_array(arr, n);

    for (int i = 0; i < n; i++)
        arr_2[i] = arr[i];

    bubbleSort(arr_2, n);

    bool* a = new bool[n];
    for (int i = 0; i < n; i++)
        a[i] = true;

    for (int i = 0; i < n - 1; i++)
    {
        if (arr_2[i] == arr_2[i + 1])
        {
            a[i] = false;
            a[i + 1] = false;
        }
    }

    int min;
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == true)
            k++;
    }

    if (k == 0)
    {
        cout << "Минимальное повтор. число: " << link_bad(arr, arr_2, n, min) << endl;
        for (int i = 0; i < n; i++)
            if (arr[i] == min)
                arr[i] = 0;
        cout_array(arr, n);
    }
    else
    {
        int num = 0;
        while (a[num] != true)
        {
            num++;
        }

        min = arr_2[num];

        cout << "Минимальное неповтор. число: " << link(arr, n, min, poz) << endl;

        arr[poz] = 0;

        cout_array(arr, n);
    }

    cin.ignore(); // Очистка буфера ввода
    cin.get();    // Ожидание нажатия клавиши

    delete[] arr;
    delete[] arr_2;
    delete[] a; // Освобождаем память
    return 0;
}

//-----------------------------------------------------------------------------------------------------

void bubbleSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; ++i)
    {
        for (int j = 0; j < size - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                // Меняем элементы местами
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void cin_array(int arr[], int size)
{
    cout << "Введите массив размером " << size << '\n';
    for (int i = 0; i < size; i++)
        cin >> arr[i];
}

void cout_array(int arr[], int size)
{
    cout << "Измененный массив:\n";
    for (int i = 0; i < size; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

int& link(int arr[], int size, int min, int& poz)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == min)
        {
            poz = i;
            return arr[i];
        }
    }
    // Если min не найден, возвращаем первый элемент
    poz = 0;
    return arr[0];
}

int& link_bad(int arr[], int arr_2[], int size, int& min)
{
    min = arr_2[0];
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == min)
        {
            return arr[i];
        }
    }
    // Если min не найден, возвращаем первый элемент
    return arr[0];
}