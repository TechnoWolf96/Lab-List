#pragma once
#include "TNode.h"

// ����� "����" ������������� � ������� ������������ ������
template <class T>
class TStackList
{
private:
	TNode<T>* pFirst;	// ��������� �� ������ ������� � ������
public:
	TStackList() { pFirst = nullptr; }					// �����������
	TStackList(const TStackList& other);				// ����������� �����������
	TStackList& operator=(const TStackList& other);		// �������� ������������
	~TStackList();										// ����������

	int Count() { return CountNodes(pFirst); }		// ������� ��������� � �����
	void Push(T item);								// �������� ������� � ����
	T Pop();										// ������� ������� �� �����
	T Top();										// ���������� ������� �� ������� �����
	void Clear();									// �������� ����
	bool IsEmpty() { return pFirst == nullptr; }	// �������� �� ���� ������

};

template<class T>
inline void TStackList<T>::Push(T item)
{
	TNode<T>* newNode = new TNode<T>();
	newNode->value = item;
	newNode->pNext = pFirst;
	pFirst = newNode;

}

template<class T>
inline T TStackList<T>::Pop()
{
	if (IsEmpty()) throw "Stack is empty";
	T value = pFirst->value;
	TNode<T>* oldFirst = pFirst;
	pFirst = oldFirst->pNext;
	delete oldFirst;

	return value;
}

template<class T>
inline T TStackList<T>::Top()
{
	if (IsEmpty()) throw "Stack is empty";
	return pFirst->value;
}

template<class T>
inline TStackList<T>::~TStackList()
{
	Clear();
}

template<class T>
inline TStackList<T>::TStackList(const TStackList& other)
{
	pFirst = nullptr;
	TNode<T>* newNode;
	TNode<T>* otherNode = other.pFirst;
	if (other.pFirst == nullptr) return;
	newNode = new TNode<T>();
	newNode->value = otherNode->value;
	newNode->pNext = nullptr;
	pFirst = newNode;
	TNode<T>* temp = pFirst;
	otherNode = otherNode->pNext;
	while (otherNode != nullptr)
	{
		newNode = new TNode<T>();
		newNode->value = otherNode->value;
		newNode->pNext = nullptr;
		temp->pNext = newNode;
		otherNode = otherNode->pNext;
		temp = temp->pNext;
	}
}

template<class T>
inline TStackList<T>& TStackList<T>::operator=(const TStackList<T>& other)
{
	Clear();
	TNode<T>* newNode;
	TNode<T>* otherNode = other.pFirst;
	if (other.pFirst == nullptr) { return *this; }
	newNode = new TNode<T>();
	newNode->value = otherNode->value;
	newNode->pNext = nullptr;
	pFirst = newNode;
	TNode<T>* temp = pFirst;
	otherNode = otherNode->pNext;
	while (otherNode != nullptr)
	{
		newNode = new TNode<T>();
		newNode->value = otherNode->value;
		newNode->pNext = nullptr;
		temp->pNext = newNode;
		otherNode = otherNode->pNext;
		temp = temp->pNext;
	}
	return *this;
}

template<class T>
inline void TStackList<T>::Clear()
{
	TNode<T>* temp;
	while (pFirst != nullptr)
	{
		temp = pFirst;
		pFirst = pFirst->pNext;
		delete temp;
	}
}