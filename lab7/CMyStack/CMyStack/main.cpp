// CMyStack.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CMyStack.h"
#include <string>

using namespace std;


int main()
{
	CMyStack<int> intStack;
	for (int i = 0; i < 100; ++i)
	{
		intStack.Push(i);
	}
	cout << "Stack size is " << intStack.Size() << endl;
	cout << "Top element is " << intStack.Top() << endl;
	intStack.Pop();
	cout << "Now top element is " << intStack.Top() << endl;

	cout << endl;

	CMyStack<string> stringStack;
	for (int i = 0; i < 100; ++i)
	{
		stringStack.Push("number" + to_string(i));
	}
	cout << "Stack size is " << stringStack.Size() << endl;
	cout << "Top element is " << stringStack.Top() << endl;
	stringStack.Pop();
	cout << "Now top element is " << stringStack.Top() << endl;
}

