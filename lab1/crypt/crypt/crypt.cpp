// crypt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string CRYPT = "crypt";
const string DECRYPT = "decrypt";

char MixByte(char& byte)
{
    char mixedByte = '0';

    ((1 << 0) & byte) == (1 << 0) ? mixedByte |= (1 << 2) : mixedByte &= ~(1 << 2);
    ((1 << 1) & byte) == (1 << 1) ? mixedByte |= (1 << 3) : mixedByte &= ~(1 << 3);
    ((1 << 2) & byte) == (1 << 2) ? mixedByte |= (1 << 4) : mixedByte &= ~(1 << 4);
    ((1 << 3) & byte) == (1 << 3) ? mixedByte |= (1 << 6) : mixedByte &= ~(1 << 6);
    ((1 << 4) & byte) == (1 << 4) ? mixedByte |= (1 << 7) : mixedByte &= ~(1 << 7);
    ((1 << 5) & byte) == (1 << 5) ? mixedByte |= (1 << 0) : mixedByte &= ~(1 << 0);
    ((1 << 6) & byte) == (1 << 6) ? mixedByte |= (1 << 1) : mixedByte &= ~(1 << 1);
    ((1 << 7) & byte) == (1 << 7) ? mixedByte |= (1 << 5) : mixedByte &= ~(1 << 5);

    return mixedByte;
}

char UnMixByte(char& byte) 
{
    char unMixedByte = '0';

    ((1 << 2) & byte) == (1 << 2) ? unMixedByte |= (1 << 0) : unMixedByte &= ~(1 << 0);
    ((1 << 3) & byte) == (1 << 3) ? unMixedByte |= (1 << 1) : unMixedByte &= ~(1 << 1);
    ((1 << 4) & byte) == (1 << 4) ? unMixedByte |= (1 << 2) : unMixedByte &= ~(1 << 2);
    ((1 << 6) & byte) == (1 << 6) ? unMixedByte |= (1 << 3) : unMixedByte &= ~(1 << 3);
    ((1 << 7) & byte) == (1 << 7) ? unMixedByte |= (1 << 4) : unMixedByte &= ~(1 << 4);
    ((1 << 0) & byte) == (1 << 0) ? unMixedByte |= (1 << 5) : unMixedByte &= ~(1 << 5);
    ((1 << 1) & byte) == (1 << 1) ? unMixedByte |= (1 << 6) : unMixedByte &= ~(1 << 6);
    ((1 << 5) & byte) == (1 << 5) ? unMixedByte |= (1 << 7) : unMixedByte &= ~(1 << 7);

    return unMixedByte;
}



void crypt(istream& fIn, ostream& fOut, int key)
{
    char byte;

    while (fIn.get(byte))
    {
        byte ^= key;
        byte = MixByte(byte);
        fOut.put(byte);
    }
}

void decrypt(istream& fIn, ostream& fOut, int key)
{
    char byte;

    while (fIn.get(byte))
    {
        byte = UnMixByte(byte);
        byte ^= key;
        fOut.put(byte);
    }
}

void ParseArguments(int argc, char* argv[])
{
    if (argc != 5)
    {
        throw runtime_error("Invalid argument count\nUsage: crypt.exe crypt/decrypt <inputFile> <outputFile> <key>\n");
    }

    int key;
    if (!(key = stoi(argv[4])))
    {
        throw runtime_error("Invalid argument\nEnter number from 0 to 255\n");
    }
    if (key < 0 || key > 255)
    {
        throw runtime_error("Invalid key\nEnter number from 0 to 255\nTry again.\n");
    }

    string command = argv[1];
    if (command != CRYPT && command != DECRYPT)
    {
        throw runtime_error("Invalid command\nEnter command 'crypt' or 'decryt'\nTry again.\n");
    }

}

int main(int argc, char* argv[])
{

    try
    {
        ParseArguments(argc, argv);
    }
    catch (const exception ex)
    {
        cout << ex.what();
        return 1;
    }

    ifstream fIn(argv[2], ios::binary);
    if (!fIn.is_open()) {
        cout << "An error occurred opening the input file.\nTry again.\n";
        return 1;
    }

    ofstream fOut(argv[3], ios::binary);
    if (!fOut.is_open())
    {
        cout << "An error occurred opening the output file.\nTry again.\n";
        return 1;
    }

    int key;
    key = stoi(argv[4]);
   
    string command = argv[1];
    if (command == CRYPT)
    {
        crypt(fIn, fOut, key);
    }
    else 
    {
        decrypt(fIn, fOut, key);
    }

    return 0;
}
