#pragma once
#include <string>
#include "TStackList.h"
#include <math.h>
#define VIRGULE '.'		// Какой символ является запятой-разделителем целой и дробной части вещественных чисел

using namespace std;

class TCalculatorList
{
private:
	string expression;				// Алгебраическое выражение
	string postfix;					// Постфиксная запись выражения
	TStackList<double> numberStack;		// Стек с числами
	TStackList<char> operatorStack;		// Стек с операторами и скобками

	const string operators = "+-/*^";		// Строка со всевозможными операторами


	void ToPostfix();				// Сохраняет постфиксную запись в строку postfix
	int Priority(char oper);		// Возвращает приоритет операции
	bool CheckExpression();			// Функция проверки введенного выражения
	bool IsOperator(char symbol);	// Функция проверяет, есть ли оператором переданный символ
	void ClearStacks();				// Очистка стеков

public:

	TCalculatorList(string expression = "");				// Конструктор
	TCalculatorList(const TCalculatorList& other);				// Конструктор копирования
	~TCalculatorList() {}									// Деструктор
	TCalculatorList& operator=(const TCalculatorList& other);	// Присваивание
	void SetExpression(string expression);				// Сеттер
	string GetExpression() { return expression; }		// Геттер
	string GetPostfix() { return postfix; }				// Получить постфиксную запись
	
	double CalculatePostfix();	// Вычисление значения выражения, используя строку postfix
	double Calculate();			// Вычисление выражения без использования заранее подготовленной строки postfix
};

inline void TCalculatorList::ClearStacks()
{
	numberStack.Clear();
	operatorStack.Clear();
}

inline bool TCalculatorList::IsOperator(char symbol)
{
	for (int i = 0; i < operators.length(); i++)
	{
		if (symbol == operators[i]) return true;
	}
	return false;
}


inline TCalculatorList::TCalculatorList(string expression)
{
	this->expression = expression;
	numberStack = TStackList<double>();
	operatorStack = TStackList<char>();
	if (!CheckExpression()) throw "Wrong expression";
	ToPostfix();
	
}

inline TCalculatorList::TCalculatorList(const TCalculatorList& other)
{
	expression = other.expression;
	postfix = other.postfix;
	numberStack = TStackList<double>();
	operatorStack = TStackList<char>();

}

inline TCalculatorList& TCalculatorList::operator=(const TCalculatorList& other)
{
	expression = other.expression;
	postfix = other.postfix;
	numberStack = other.numberStack;
	operatorStack = other.operatorStack;
}

inline void TCalculatorList::SetExpression(string expression)
{
	this->expression = expression;
	if (!CheckExpression()) throw "Wrong expression";
	ToPostfix();
	numberStack.~TStackList();
	operatorStack.~TStackList();
	numberStack = TStackList<double>();
	operatorStack = TStackList<char>();
}

inline bool TCalculatorList::CheckExpression()
{
	ClearStacks();

	// Проверяем что выражение - это последовательность: число, операция, число, операция и т.д (Скобки игнорируем)
	for (int i = 0; i < expression.size(); i++)
	{
		if (!isdigit(expression[i]) && !IsOperator(expression[i]) && expression[i] != '('
			&& expression[i] != ')' && expression[i] != ' ') return false;
		if (isdigit(expression[i]))
		{
			size_t addIndex;
			operatorStack.Push('n');
			stod(&expression[i], &addIndex);
			if (operatorStack.Count() > 1)
				return false;
			i += addIndex;
		}
		
		if (IsOperator(expression[i]))
		{
			try { operatorStack.Pop(); }
			catch (...) { return false; }
		}
		if (operatorStack.Count() > 1)
			return false;
	}
	ClearStacks();
	// Проверка правильности расстановки скобок
	for (int i = 0; i < expression.size(); i++)
	{
		if (expression[i] == '(') operatorStack.Push('(');
		try
		{
			if (expression[i] == ')') operatorStack.Pop();
		}
		catch (...)
		{
			return false;
		}
	}
	if (!operatorStack.IsEmpty()) return false;
	return true;
}

inline double TCalculatorList::CalculatePostfix()
{
	ClearStacks();
	for (int i = 0; i < postfix.length(); i++)
	{
		if (isdigit(postfix[i])) // Если в постфиксной записи попалось число то:
		{
			size_t addIndex;
			double number = stod(&postfix[i], &addIndex);
			numberStack.Push(number);	// Добавляем его в стек с числами
			i += addIndex;	// Переводим текущий индекс на начало следующей операции/операнда
		}
			
		if (IsOperator(postfix[i]))	// Встретился знак - нужно произвести данную операцию над двумя последними в стеке числами
		{
			double second = numberStack.Pop();
			double first = numberStack.Pop();
			switch (postfix[i])
			{
			case '+': numberStack.Push(first + second); break;
			case '-': numberStack.Push(first - second); break;
			case '*': numberStack.Push(first * second); break;
			case '/': numberStack.Push(first / second); break;
			case '^': numberStack.Push(pow(first, second)); break;
			}
		}
	}
	return numberStack.Pop();
}

inline double TCalculatorList::Calculate()
{
	ClearStacks();
	string infix = '(' + expression + ')';
	for (int i = 0; i < infix.length(); i++)
	{
		if (isdigit(infix[i])) // Если в постфиксной записи попалось число то:
		{
			size_t addIndex;
			double number = stod(&infix[i], &addIndex);
			numberStack.Push(number);	// Добавляем его в стек с числами
			i += addIndex;	// Переводим текущий индекс на начало следующей операции/операнда
		}
		if (infix[i] == '(') // Встретилась скобка - кладем в стек операций
			operatorStack.Push(infix[i]);
			
		if (IsOperator(infix[i]))	// Встретился оператор
		{
			// Попалась менее/равноприоритеная операция - выполняем ту, что на вершине стека
			while (Priority(infix[i]) <= Priority(operatorStack.Top())) 
			{
				double second = numberStack.Pop();
				double first = numberStack.Pop();
				switch (operatorStack.Pop())
				{
				case '+': numberStack.Push(first + second); break;
				case '-': numberStack.Push(first - second); break;
				case '*': numberStack.Push(first * second); break;
				case '/': numberStack.Push(first / second); break;
				case '^': numberStack.Push(pow(first, second)); break;
				}
			}
			// И кладем в стек новую операцию
			operatorStack.Push(infix[i]);
		}
		if (infix[i] == ')')	// Встретилась закрывающая скобка - выполняем операции в стеке до открывающей скобки
		{
			while (operatorStack.Top() != '(')
			{
				double second = numberStack.Pop();
				double first = numberStack.Pop();
				switch (operatorStack.Pop())
				{
				case '+': numberStack.Push(first + second); break;
				case '-': numberStack.Push(first - second); break;
				case '*': numberStack.Push(first * second); break;
				case '/': numberStack.Push(first / second); break;
				case '^': numberStack.Push(pow(first, second)); break;
				}
			}
			operatorStack.Pop(); // Убрали открывающую скобку
		}

	}
	return numberStack.Pop();
}

inline void TCalculatorList::ToPostfix()
{
	ClearStacks();
	string infix = "(" + expression + ")";
	postfix = "";
	for (int i = 0; i < infix.size(); i++)
	{
		if (isdigit(infix[i]))	// Встретили цифру
		{
			// Считываем полностью вещественное число (Даже в виде 10e5, 10e-5)
			while ((isdigit(infix[i]) || infix[i] == VIRGULE || infix[i] == 'e' ||
				(i > 0 && infix[i - 1] == 'e' && infix[i] == '-')) && i < infix.size())
			{
				postfix += infix[i];
				i++;
			}
			postfix += ' ';
		}
		if (infix[i] == '(') operatorStack.Push(infix[i]);
		if (infix[i] == ')')
		{
			while (operatorStack.Top() != '(')
				postfix = postfix + operatorStack.Pop() + ' ';
			operatorStack.Pop();
		}
		if (IsOperator(infix[i]))
		{
			while (Priority(infix[i]) <= Priority(operatorStack.Top()))
			{
				postfix = postfix + operatorStack.Pop() + ' ';
			}
			operatorStack.Push(infix[i]);
		}

	}

}
inline int TCalculatorList::Priority(char oper)
{
	if (oper == '(') return 0;
	if (oper == '+' || oper == '-') return 1;
	if (oper == '*' || oper == '/') return 2;
	if (oper == '^') return 3;
}