// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int FlipByte(int& number) {

    number = ((number & 0b1111) << 4) | ((number & 0b11110000) >> 4);
    number = ((number & 0b110011) << 2) | ((number & 0b11001100) >> 2);
    number = ((number & 0b01010101) << 1) | ((number & 0b10101010) >> 1);
    
    return number;
}

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        cout << "Invalid argument count\n"
            << "Usage: flipbyte.exe <number>\n";
        return 1;
    }

    if (argv[1][0] < '0' || argv[1][0] > '9')
    {
        cout << "Invalid argument\nEnter number from 0 to 255\n";
        return 1;
    }

    int number;
    number = stoi(argv[1]);
    if (number < 0 || number > 255)
    {
        cout << "Invalid key\nEnter number from 0 to 255\n";
        return 1;
    }

    cout << FlipByte(number) << endl;

    return 0;
}
