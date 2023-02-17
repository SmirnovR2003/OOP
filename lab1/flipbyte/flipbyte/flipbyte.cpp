// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int CharToInt(char ch)
{
    switch (ch)
    {
    case '0':
        return 0;
    case '1':
        return 1;
    case '2':
        return 2;
    case '3':
        return 3;
    case '4':
        return 4;
    case '5':
        return 5;
    case '6':
        return 6;
    case '7':
        return 7;
    case '8':
        return 8;
    case '9':
        return 9;
    default:
        return -1;
    }
}

int StringToInt(const string& str)
{

    int returnNumber = 0;

    for (int i = 0; i < str.length(); i++)
    {
        if (CharToInt(str[i]) == -1)
        {
            return returnNumber;
        }
        else 
        {
            returnNumber = returnNumber * 10 + CharToInt(str[i]);
        }
    }
    return returnNumber;
}

void GetReverseBinary(int n, string& binaryNumber)
{
    if (n / 2 != 0) {
        GetReverseBinary(n / 2, binaryNumber);
    }

    binaryNumber = to_string(n % 2) + binaryNumber;
}

double BinToDec(string binaryNumber) {
    double number = 0;
    for (int i = 0; i < binaryNumber.size(); i++)
        if (binaryNumber[i] == '1')
            number += pow(2, binaryNumber.size() - i - 1);

    return number;
}

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
            << "Usage: <number>\n";
        return 1;
    }

    if (argv[1][0] < '0' || argv[1][0] > '9') 
    {
        cout << "Invalid argument\nEnter number from 0 to 255\n";
        return 1;
    }

    int number = StringToInt(argv[1]);

    if (number < 0 || number > 255)
    {
        cout << "Invalid argument\nEnter number from 0 to 255\n";
        return 1;
    }

    cout << FlipByte(number) << endl;

    return 0;
}
