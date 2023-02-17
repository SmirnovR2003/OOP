// Replace.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string ReplaceString(const string& subject, const string& searchString, const string& replacementString)
{
    size_t pos = 0;
    string result;

    if (replacementString.empty() || searchString.empty()) {
        return subject;
    }

    while (pos < subject.length())
    {
        size_t foundPos = subject.find(searchString, pos);
         
        if (foundPos == string::npos)
        {
            result.append(subject, pos, subject.length() - pos);
            break;
        }

        result.append(subject, pos, foundPos - pos);

        pos = foundPos + searchString.length();

        result.append(replacementString);
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

    if (!fOut.flush()) {
        cout << "Error writing to file\n";
        return 1;
    }

    return 0;
}
