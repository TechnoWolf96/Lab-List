#include <iostream>
#include "TQueueList.h"
using namespace std;

void TestTQueueList()
{
    cout << "������������ ������� �� ��������." << endl;
    TQueueList<int> a;
    cout << "������� ������� �. ������� � �����? �����: " << a.IsEmpty() << "; ���������� ��������� �: " << a.Count() << endl;
    a.Push(1), a.Push(2), a.Push(3);
    cout << "������� ���� �������� 1, 2, 3. ������� � �����? �����: " << a.IsEmpty() << "; ���������� ��������� �: " << a.Count() << endl;
    TQueueList<int> b(a), c;
    cout << "��������� ������� � � ������� �: ������� � �����? �����: " << b.IsEmpty() << "; ���������� ��������� �: " << b.Count() << endl;
    cout << "�������� ��� �������� �� ������� �:" << endl;
    while (!b.IsEmpty())
    {
        cout << "�������� ������� " << b.Pop(); 
        cout << "; �������� ��������� � �: " << b.Count() << endl;
    }
    b.Push(4), b.Push(5);
    cout << "� ������� � ��������� �������� 4 � 5." << endl;
    c = b;
    cout << "������� � ��������� ������� �." << endl;
    cout << "�������� ��� �������� �� ������� C:" << endl;
    while (!c.IsEmpty())
    {
        cout << "�������� ������� " << c.Pop();
        cout << "; �������� ��������� � C: " << c.Count() << "; �������� ��������� � �: " << b.Count() << endl;
    }



}





int __main()
{
    setlocale(LC_ALL, "ru");

    TestTQueueList();

    cout << endl;
    system("pause");
    return 0;
}