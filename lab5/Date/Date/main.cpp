// Date.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "CDate.h"


int main()
{
    CDate date;
    while (std::cin >> date)
    {
        std::cout << date;
    }

}

