#include <iostream>
#include "TStackList.h"
using namespace std;

void TestTStackList()
{
    cout << "Тестирование cтека со списками." << endl;
    TStackList<int> a, c;
    cout << "Создан стек А. Стек А пуст? Ответ: " << a.IsEmpty() << endl;

    a.Push(1), a.Push(2); a.Push(3);
    cout << "Добавлены элементы 1, 2, 3 в стек А. Стек А пуст? Ответ: " << a.IsEmpty() << "; Количество элементов в стеке А: " << a.Count() << endl;

    cout << "Извлечен элемент из А: " << a.Pop(); 
    cout << ". На вершине стека А теперь: " << a.Top() << endl;
    
    TStackList<int> b(a);
    cout << "В стек В скопирован стек А. Элемент на вершине стека В: " << b.Top() << endl;
    cout << "Извлечен элемент из B: " << b.Pop();
    cout << ". На вершине стека B теперь: " << b.Top() << endl;
    c = a;
    cout << "Стеку С присвоен стек А. Элемент на вершине стека С: " << c.Top() << endl;
    cout << "Извлечен элемент из C: " << c.Pop();
    cout << ". На вершине стека C теперь: " << c.Top() << endl;
    c.Clear();
    cout << "Стек С очищен." << endl;
    cout << "Текущее количество элементов в стеках:\nA: " << a.Count() << "\nB: " << b.Count() << "\nC: " << c.Count();

}





int _main()
{
    setlocale(LC_ALL, "ru");

    TestTStackList();

    cout << endl;
    system("pause");
    return 0;
}