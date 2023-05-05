// CMyString.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <algorithm>
#include "CMyString.h"

int main()
{
    CMyString str3("1230");

    auto it = str3.begin();

    std::cout << *it;
    it++;

    std::cout << *it;
    it++;

    std::cout << *it;
    it++;

    std::cout << *it;
    it++;
}