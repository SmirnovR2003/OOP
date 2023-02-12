// flipbyte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void toBinary(int n, string& binaryNumber)
{
    if (n / 2 != 0) {
        toBinary(n / 2, binaryNumber);
    }

    binaryNumber = to_string(n % 2) + binaryNumber;
}

void FlipByte(string binaryNumber) {
    while (binaryNumber.size() < 8) {
        binaryNumber += "0";
    }

    int number = 0;
    for (int i = 0; i < binaryNumber.size(); i++)//    пошли по строке бит
        if (binaryNumber[i] == '1')   // если i-й бит в строке = 1 ,
            number += pow(2, binaryNumber.size() - i - 1);

    cout << number << endl;
}

int main(int argc, char* argv[])
{

    if (argc != 2)
    {
        cout << "Invalid argument count\n"
            << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
        return 1;
    }

    if (argv[1][0] < '0' || argv[1][0] > '9') {
        cout << "Invalid argument\n Enter number from 0 to 255\n";
        return 1;
    }

    int number = stoi(argv[1]);

    if (number < 0 || number > 255) {
        cout << "Invalid argument\n Enter number from 0 to 255\n";
        return 1;
    }

    string binaryNumber;

    toBinary(number, binaryNumber);
    FlipByte(binaryNumber);

    return 0;
}
