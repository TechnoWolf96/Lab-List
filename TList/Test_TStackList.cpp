#include <iostream>
#include "TStackList.h"
using namespace std;

void TestTStackList()
{
    cout << "������������ c���� �� ��������." << endl;
    TStackList<int> a, c;
    cout << "������ ���� �. ���� � ����? �����: " << a.IsEmpty() << endl;

    a.Push(1), a.Push(2); a.Push(3);
    cout << "��������� �������� 1, 2, 3 � ���� �. ���� � ����? �����: " << a.IsEmpty() << "; ���������� ��������� � ����� �: " << a.Count() << endl;

    cout << "�������� ������� �� �: " << a.Pop(); 
    cout << ". �� ������� ����� � ������: " << a.Top() << endl;
    
    TStackList<int> b(a);
    cout << "� ���� � ���������� ���� �. ������� �� ������� ����� �: " << b.Top() << endl;
    cout << "�������� ������� �� B: " << b.Pop();
    cout << ". �� ������� ����� B ������: " << b.Top() << endl;
    c = a;
    cout << "����� � �������� ���� �. ������� �� ������� ����� �: " << c.Top() << endl;
    cout << "�������� ������� �� C: " << c.Pop();
    cout << ". �� ������� ����� C ������: " << c.Top() << endl;
    c.Clear();
    cout << "���� � ������." << endl;
    cout << "������� ���������� ��������� � ������:\nA: " << a.Count() << "\nB: " << b.Count() << "\nC: " << c.Count();

}





int _main()
{
    setlocale(LC_ALL, "ru");

    TestTStackList();

    cout << endl;
    system("pause");
    return 0;
}