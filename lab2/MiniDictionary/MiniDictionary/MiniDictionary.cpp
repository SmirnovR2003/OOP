#include "MiniDictionary.h"
#include <map>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

map<string, string> ReadDictionaryFromFile(istream& cIn, ostream& cOut, string& dictionaryFileName, bool& isFilledDictionary)
{
	map<string, string> dictionary{};

	ifstream dictionaryFile(dictionaryFileName);
	if (!dictionaryFile.is_open())
	{
		cOut << "������ �������� �����-�������.\n���������� ��� ���������� ������� � ��������� ��� ��������� � dictionary.txt?(Y/N)\n>";
		
		string answer;
		getline(cIn, answer);
		if (answer == "Y" || answer == "y") isFilledDictionary = true;
		else isFilledDictionary = false;

		dictionaryFileName = "dictionary.txt";
		return map<string, string>{};
	}
	else
	{
		string eng, rus;
		while (getline(dictionaryFile, eng) && getline(dictionaryFile, rus))
		{
			dictionary[eng] = rus;
		}
		isFilledDictionary = true;
		return dictionary;
	}
	dictionaryFile.close();
}

void SaveFile(ostream& cOut, const string& dictionaryFileName, const map<string, string>& dictionary, const vector<string>& newWords)
{
	ofstream dictionaryFile(dictionaryFileName, ios::app);
	if (!dictionaryFile.is_open())
	{
		cOut << "������ ��� ���������� �������\n";
		return;
	}


	for (const auto& word : newWords)
	{
		dictionaryFile << word << endl << dictionary.find(word)->second << endl;
	}

	if(dictionaryFile.flush()) cOut << "��������� ���������. �� ��������.\n";
	else cOut << "������ ��� ���������� �������\n";

	dictionaryFile.close();
}

void DialogueWithUser(istream& cIn, ostream& cOut, string& dictionaryFileName)
{
	//wasChanges -> isChanged
	bool wasChanges = false, isFilledDictionary = false;

	map<string, string> dictionary = ReadDictionaryFromFile(cIn, cOut, dictionaryFileName, isFilledDictionary);

	if (!isFilledDictionary) return;
	string word;
	vector<string> newWords;

	//��� �������
	cOut << '>';
	while (getline(cIn, word))
	{
		if (word == "...") break;

		if (dictionary.find(word) == dictionary.end())
		{
			//�������� � �������
			cOut << "����������� ����� \"" << word << "\". ������� ������� ��� ������ ������ ��� ������.\n";

			cOut << '>';
			string answer;
			getline(cIn, answer);

			if (answer == "") 
			{
				cOut << "����� \"" << word << "\" ���������������.\n";
			}
			else
			{
				dictionary[word] = answer;
				newWords.push_back(word);

				cOut << "����� \"" << word << "\" ��������� � ������� ��� \"" << answer << "\"\n";
				wasChanges = true;
			}
		}
		else
		{
			//��������� �������� � ����������

			//if (auto it = find; it != coll.end())
			cOut << dictionary.find(word)->second << endl;
		}
		cout << '>';
	}

	//���������� ���������
	if (wasChanges)
	{
		//��������� �������
		cOut << "� ������� ���� ������� ���������. ������� Y ��� y ��� ���������� ����� �������.\n";

		cOut << '>';
		char answer;
		cIn.get(answer);

		if (answer == 'Y' || answer == 'y') SaveFile(cOut, dictionaryFileName, dictionary, newWords);
	}
}

