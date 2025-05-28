#include <iostream>

using namespace std;

struct List
{
    double val;
    List* prev;
    List* next;

    List(double val)
    {
        this->val = val; 
        this->prev = nullptr;
        this->next = nullptr;
    }
};

int main()
{
    int n;
    cin >> n;

    List* head = nullptr;
    List* tail = nullptr;

    for (int i = 0; i < n; i++)
    {
        double x;
        cin >> x;

        List* newList = new List(x);
        if(!head)
        {
            head = tail = newList;
        }
        else
        {
            tail->next = newList;
            newList->prev = tail;
            tail = newList;
        }
    }
List* current = head;
    while(current)
    {
        cout << current->val << ' ';
        current = current->next;
    }


    List* current1 = head;
    while (current1)
    {
        List* newList = current1->next;
        delete current1;
        current1 = newList;
    }
    
    cin.ignore();
    cin.get();
    return 0;
}