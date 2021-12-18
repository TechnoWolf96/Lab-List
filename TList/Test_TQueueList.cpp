#include <iostream>
#include "TQueueList.h"
using namespace std;

void TestTQueueList()
{
    cout << "Тестирование очереди со списками." << endl;
    TQueueList<int> a;
    cout << "Создана очередь А. Очередь А пуста? Ответ: " << a.IsEmpty() << "; Количество элементов А: " << a.Count() << endl;
    a.Push(1), a.Push(2), a.Push(3);
    cout << "Добавим туда элементы 1, 2, 3. Очередь А пуста? Ответ: " << a.IsEmpty() << "; Количество элементов А: " << a.Count() << endl;
    TQueueList<int> b(a), c;
    cout << "Скопируем очередь А в очередь В: Очередь В пуста? Ответ: " << b.IsEmpty() << "; Количество элементов В: " << b.Count() << endl;
    cout << "Извлечем все элементы из очереди В:" << endl;
    while (!b.IsEmpty())
    {
        cout << "Извлечен элемент " << b.Pop(); 
        cout << "; Осталось элементов в В: " << b.Count() << endl;
    }
    b.Push(4), b.Push(5);
    cout << "В очередь В добавлены элементы 4 и 5." << endl;
    c = b;
    cout << "Очереди С присвоена очередь В." << endl;
    cout << "Извлечем все элементы из очереди C:" << endl;
    while (!c.IsEmpty())
    {
        cout << "Извлечен элемент " << c.Pop();
        cout << "; Осталось элементов в C: " << c.Count() << "; Осталось элементов в В: " << b.Count() << endl;
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