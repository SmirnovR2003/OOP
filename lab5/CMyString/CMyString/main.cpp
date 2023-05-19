// CMyString.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <algorithm>
#include "CMyString.h"

using namespace std;

int main()
{
    CMyString str("qqwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZCXVBNM");
    cout << str << endl;
    sort(str.begin(), str.end());
    cout << str << endl;
}