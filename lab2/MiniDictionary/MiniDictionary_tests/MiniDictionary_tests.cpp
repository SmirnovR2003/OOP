// MiniDictionary_tests.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MiniDictionary/MiniDictionary.h"
#include "sstream"

using namespace std;

SCENARIO("SaveFile function tests")
{
	SECTION("Check with only-read file")
	{
		string dictionaryFileName = "dic1.txt";
		map<string, string> dictionary{ {"meet", "мясо"} };
		vector<string> newWords{ "meet" };
		ostringstream fOut("");

		SaveFile(fOut, dictionaryFileName, dictionary, newWords);
		CHECK("Ошибка при сохранении словаря\n" == fOut.str());
	}

	SECTION("Check with norm file")
	{
		string dictionaryFileName = "dic2.txt";
		map<string, string> dictionary{ {"meet", "мясо"} };
		vector<string> newWords{ "meet" };
		ostringstream fOut("");

		SaveFile(fOut, dictionaryFileName, dictionary, newWords);
		CHECK("Изменения сохранены. До свидания.\n" == fOut.str());
	}
}

SCENARIO("ReadDictionaryFromFile function tests")
{
	SECTION("Check with unread file")
	{
		string dictionaryFileName = "dic1.txt";
		map<string, string>dictionary1;
		bool isReadFile;
		istringstream fIn("Y\n");
		ostringstream fOut("");

		ReadDictionaryFromFile(fIn, fOut, dictionaryFileName, isReadFile);
		CHECK("Ошибка открытия файла-словаря.\nПродолжить без начального словаря и сохранить все изменения в dictionary.txt?(Y/N)\n>" == fOut.str());
		CHECK(isReadFile);
	}

	SECTION("Check with norm file")
	{
		string dictionaryFileName = "dic2.txt";
		map<string, string>dictionary1, dictionary2{ {"meet", "мясо"}, {"egg", "яйцо"} };
		bool isReadFile;
		istringstream fIn("");
		ostringstream fOut("");

		dictionary1 = ReadDictionaryFromFile(fIn, fOut, dictionaryFileName, isReadFile);
		CHECK(isReadFile);
		CHECK(dictionary1 == dictionary1);
	}
}

SCENARIO("DialogueWithUser function tests")
{
	SECTION("Check with not norm file")
	{
		string stringOut, dictionaryFileName = "dic1.txt";
		istringstream fIn("Y\nmeet\nмясо\negg\nяйцо\nasdf\n\n...\nY\n");
		ostringstream fOut("");

		stringOut += "Ошибка открытия файла-словаря.\nПродолжить без начального словаря и сохранить все изменения в dictionary.txt?(Y/N)\n>>";
		stringOut += "Неизвестное слово \"meet\". Введите перевод или пустую строку для отказа.\n>";
		stringOut += "Слово \"meet\" сохранено в словаре как \"мясо\"\n";
		stringOut += "Неизвестное слово \"egg\". Введите перевод или пустую строку для отказа.\n>";
		stringOut += "Слово \"egg\" сохранено в словаре как \"яйцо\"\n";
		stringOut += "Неизвестное слово \"asdf\". Введите перевод или пустую строку для отказа.\n>";
		stringOut += "Слово \"asdf\" проигнорировано.\n";
		stringOut += "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n>";
		stringOut += "Изменения сохранены. До свидания.\n";

		DialogueWithUser(fIn, fOut, dictionaryFileName);
		CHECK(stringOut == fOut.str());
	}

	SECTION("Check with norm file")
	{
		setlocale(LC_ALL, "rus");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		string stringOut, dictionaryFileName = "dic3.txt";
		istringstream fIn("meet\negg\nThe Red Square\nasdf\n\n...\n");
		ostringstream fOut("");

		stringOut += ">мясо\n";
		stringOut += "яйцо\n";
		stringOut += "Красная площадь\n";
		stringOut += "Неизвестное слово \"asdf\". Введите перевод или пустую строку для отказа.\n>";
		stringOut += "Слово \"asdf\" проигнорировано.\n";

		DialogueWithUser(fIn, fOut, dictionaryFileName);
		CHECK(stringOut == fOut.str());
	}
}