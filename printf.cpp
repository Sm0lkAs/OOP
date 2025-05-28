#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string path_name = "output.txt";

    ofstream fout;
    fout.open(path_name, fstream::app);

    if (!fout.is_open())
    {
        cout << "Unable to open file";
        return 1;
    }
    else
    {
        fout << "Hello!\n";
    }

    ifstream fin;
    fin.open("f.txt");

    if (!fin.is_open())
    {
        cout << "Unable to open file";
    }
    else
    {
        cout << "File opened successfully.\n";
        char ch;
        double number;
        while (!fin.eof())
        {   
            number = 0;
            fin >> number;
            cout << number << '|' << endl;
        }
    }


    fout.close();
    fin.close();

    std::cin.ignore();
    std::cin.get();
    return 0;
}