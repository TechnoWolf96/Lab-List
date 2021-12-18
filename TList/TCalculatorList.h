#pragma once
#include <string>
#include "TStackList.h"
#include <math.h>
#define VIRGULE '.'		// ����� ������ �������� �������-������������ ����� � ������� ����� ������������ �����

using namespace std;

class TCalculatorList
{
private:
	string expression;				// �������������� ���������
	string postfix;					// ����������� ������ ���������
	TStackList<double> numberStack;		// ���� � �������
	TStackList<char> operatorStack;		// ���� � ����������� � ��������

	const string operators = "+-/*^";		// ������ �� ������������� �����������


	void ToPostfix();				// ��������� ����������� ������ � ������ postfix
	int Priority(char oper);		// ���������� ��������� ��������
	bool CheckExpression();			// ������� �������� ���������� ���������
	bool IsOperator(char symbol);	// ������� ���������, ���� �� ���������� ���������� ������
	void ClearStacks();				// ������� ������

public:

	TCalculatorList(string expression = "");				// �����������
	TCalculatorList(const TCalculatorList& other);				// ����������� �����������
	~TCalculatorList() {}									// ����������
	TCalculatorList& operator=(const TCalculatorList& other);	// ������������
	void SetExpression(string expression);				// ������
	string GetExpression() { return expression; }		// ������
	string GetPostfix() { return postfix; }				// �������� ����������� ������
	
	double CalculatePostfix();	// ���������� �������� ���������, ��������� ������ postfix
	double Calculate();			// ���������� ��������� ��� ������������� ������� �������������� ������ postfix
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

	// ��������� ��� ��������� - ��� ������������������: �����, ��������, �����, �������� � �.� (������ ����������)
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
	// �������� ������������ ����������� ������
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
		if (isdigit(postfix[i])) // ���� � ����������� ������ �������� ����� ��:
		{
			size_t addIndex;
			double number = stod(&postfix[i], &addIndex);
			numberStack.Push(number);	// ��������� ��� � ���� � �������
			i += addIndex;	// ��������� ������� ������ �� ������ ��������� ��������/��������
		}
			
		if (IsOperator(postfix[i]))	// ���������� ���� - ����� ���������� ������ �������� ��� ����� ���������� � ����� �������
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
		if (isdigit(infix[i])) // ���� � ����������� ������ �������� ����� ��:
		{
			size_t addIndex;
			double number = stod(&infix[i], &addIndex);
			numberStack.Push(number);	// ��������� ��� � ���� � �������
			i += addIndex;	// ��������� ������� ������ �� ������ ��������� ��������/��������
		}
		if (infix[i] == '(') // ����������� ������ - ������ � ���� ��������
			operatorStack.Push(infix[i]);
			
		if (IsOperator(infix[i]))	// ���������� ��������
		{
			// �������� �����/���������������� �������� - ��������� ��, ��� �� ������� �����
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
			// � ������ � ���� ����� ��������
			operatorStack.Push(infix[i]);
		}
		if (infix[i] == ')')	// ����������� ����������� ������ - ��������� �������� � ����� �� ����������� ������
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
			operatorStack.Pop(); // ������ ����������� ������
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
		if (isdigit(infix[i]))	// ��������� �����
		{
			// ��������� ��������� ������������ ����� (���� � ���� 10e5, 10e-5)
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