#include "MiniDictionary.h"
#include <iostream>
#include <Windows.h>

using namespace std;

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    string dictionaryFileName = argv[1] ? argv[1] : "";
    DialogueWithUser(cin, cout, dictionaryFileName);

    return 0;
}

