// Replace.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

using namespace std;

string ReplaceString(const string& subject, const string& searchString, const string& replacementString)
{
    size_t pos = 0;
    size_t replaceCounter = 0;
    string result;

    while (pos < subject.length())
    {
        int foundPos = subject.find(searchString, pos);
        if (foundPos == -1 && replaceCounter == 0)
        {
            result = subject;
            pos = subject.length();
            continue;
        }
        else if (foundPos == -1 && replaceCounter != 0)
        {
            cout << 121332;
            result.append(subject, pos, subject.length() - pos);
            pos = subject.length();
            continue;
        }

        result.append(subject, pos, foundPos - pos);

        pos = foundPos + searchString.length();

        result.append(replacementString, 0, replacementString.length());
        replaceCounter++;
    };
    return result;
}

void CopyStreamWithReplacement(istream& fIn, ostream& fOut, const string& searchString, const string& replacementString)
{
    string line;

    while (getline(fIn, line))
    {
        fOut << ReplaceString(line, searchString, replacementString) << "\n";
    }
}

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    if (argc != 5)
    {
        cout << "Invalid argument count\n"
            << "Usage: replace.exe <inputFile> <outputFile> <searchString> <replacementString>\n";
        return 1;
    }

    ifstream fIn(argv[1]);
    if (!fIn.is_open()) {
        cout << "An error occurred opening the input file.\nTry again.";
        return 1;
    }

    ofstream fOut(argv[2]);
    if (!fOut.is_open()) 
    {
        cout << "An error occurred opening the output file.\nTry again.";
        return 1;
    }

    const string SEARCH_STRING = argv[3];
    const string REPLACE_STRING = argv[4];

    CopyStreamWithReplacement(fIn, fOut, SEARCH_STRING, REPLACE_STRING);

    fOut.flush();

    return 0;
}
