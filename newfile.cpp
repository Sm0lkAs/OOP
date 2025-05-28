#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input_file;
    ofstream output_file("output1.txt");

    input_file.open("input1.txt");

    if(!input_file.is_open())
    cout << "File can not open\n";
    else
    {
        string s;
        cout << input_file.rdbuf();
        input_file.clear();
        input_file.seekg(0);
        getline(input_file, s);
        cout << endl << s;
    }
    output_file.close();
    input_file.close();

    cin.ignore();
    cin.get();
    return 0;
}