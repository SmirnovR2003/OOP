// HTMLDecode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include "HTMLDecode.h"

using namespace std;

int main()
{
    string html;
    while (cin >> html)
    {
        cout << HtmlDecode(html) << endl;
        
    }
}
