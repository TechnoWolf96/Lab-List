#include "TList.h"
using namespace std;

void TestTList()
{
    TList<int> a;
    cout << "������ ������ �." << endl;
    a.Add(1), a.Add(-2), a.Add(123), a.Add(-100), a.Add(100), a.Add(25);
    cout << "��������� ����� ��������. ������ �: "; a.Print();

    cout << "\n������� ������������� ��������: " << a.GetIndexMaxElem() << endl;
    int item = 18;
    a.AddAfterMax(item);
    cout << "������� " << item << " �������� � ������ � ����� �������������. ������ �: "; a.Print();
    TList<int> b;
    cout << "\n������ ������ ������ B." << endl;
    b.AddAfterMax(item);
    cout << "������� " << item << " �������� � ������ � ����� �������������. ������ �: "; b.Print();


}


int main()
{
    setlocale(LC_ALL, "ru");
    TestTList();

    cout << endl;
    system("pause");
    return 0;
}