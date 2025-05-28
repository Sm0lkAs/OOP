#include <iostream>

using namespace std;

void multiple(int c[],int** A, int z[], int size)
{
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            c[i] += A[i][j] * z[j];


}

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


int main() 
{

    int n;
    cout << "Enter n: ";

    cin >> n;

    cout << "Enter matrix A: \n";

    int** A_pointers = new int*[n];
    for (int i = 0; i < n; ++i) 
    {
        A_pointers[i] = new int[n];

        for (int j = 0; j < n; ++j)
        {
            cin >> A_pointers[i][j];
        }
    }
    int* x = new int[n];
    int* y = new int[n];
    int* z = new int[n];
    int* c = new int[n]{0};

    cout << "Enter vector x: \n";

    for (int i = 0; i < n; i++)
    {
        cin >> x[i];
    }

    cout << "Enter vector y: \n";

    for (int i = 0; i < n; i++)
    {
        cin >> y[i];
    }

        sum(x, y, z, n);
        multiple(c, A_pointers, z, n);
        printArray(c, n);

    cin.ignore(); // Игнорирование пустой строки
    cin.get();    // Для того, чтобы не закрывался консольный окно при запуске программ
    delete [] x;
    delete [] y;
    delete [] z;
    delete [] c;
    for (int i = 0; i < n; i++)
    {
        delete [] A_pointers[i];
        }
        delete [] A_pointers;

    
    return 0;
}
