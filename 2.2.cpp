#include <iostream>

using namespace std;

void printArray(int arr[], int size) 
{
    cout << "Array: \n";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
        }
}

    void sum(int x[], int y[], int z[], int size)
    {
        for (int i = 0; i < size; i++)
        {
            z[i] = x[i] + y[i];
        }
    }

    void A_z(int A[], int z[], int c[], int size)
    {
        for (int i = 0; i < size; i++) // A * z
        for (int j = 0; j < size; j++)
            c[i] += A[i * size + j] * z[j];
    }    


int main() 
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    int n;
    cout << "Enter number: ";
    cin >> n;

    int* A = new int [n * n]; // Матрица

    int* x = new int [n]; // Вектор

    int* y = new int [n]; // Вектор

    int* z = new int [n]; // Вектор x + y

    int* c = new int [n]{0}; // A * z

        cout << "Enter line of matrix: ";

        for (int i = 0; i < n * n; i++)
        {cin >> A[i];}

        cout << "Enter vector x: ";

        for (int i = 0; i < n; i++)
        {cin >> x[i];}

        cout << "Enter vector y: ";

        for (int i = 0; i < n; i++)
        {cin >> y[i];}

        sum(x, y, z, n);

        A_z(A, z, c, n);

        printArray(c, n);

        
    
    cin.ignore(); // Игнорирование пустой строки
    cin.get();    // Для того, чтобы не закрывался консольный окно при запуске программ

delete [] A;
delete [] x;
delete [] y;
delete [] z;
delete [] c;

    return 0;
}
