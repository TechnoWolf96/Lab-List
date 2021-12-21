#include "TList.h"
using namespace std;

void TestTList()
{
    TList<int> a;
    cout << "Создан список А." << endl;
    a.Add(1), a.Add(-2), a.Add(123), a.Add(-100), a.Add(100), a.Add(25);
    cout << "Добавлены новые элементы. Список А: "; a.Print();

    cout << "\nПозиция максимального элемента: " << a.GetIndexMaxElem() << endl;
    int item = 18;
    a.AddAfterMax(item);
    cout << "Элемент " << item << " добавлен в список А после максимального. Список А: "; a.Print();
    TList<int> b;
    cout << "\nСоздан пустой список B." << endl;
    b.AddAfterMax(item);
    cout << "Элемент " << item << " добавлен в списко В после максимального. Список В: "; b.Print();


}


int main()
{
    setlocale(LC_ALL, "ru");
    TestTList();

    cout << endl;
    system("pause");
    return 0;
}