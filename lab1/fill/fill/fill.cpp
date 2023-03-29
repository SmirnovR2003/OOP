// fill.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <ctime>
#include <conio.h>
#include <windows.h>

using namespace std;

const int fieldSize = 100;
//объявить с помощью std::array
const int fieldWithИarriersSize = fieldSize + 2;

void InitField(char(&field)[fieldWithИarriersSize][fieldWithИarriersSize])
{
	for (int i = 0; i < fieldWithИarriersSize; i++)
	{
		for (int j = 0; j < fieldWithИarriersSize; j++)
		{
			if (i == 0 || j == 0 || i == fieldWithИarriersSize - 1 || j == fieldWithИarriersSize - 1)
			{
				field[i][j] = '#';
			}
			else
			{
				field[i][j] = ' ';
			}
			
		}
	}
}

//заменить ifstream на istream

//обзвать lowerSymbol
//иннициализировать входные параметры
// ввести структуру point
void ReadField(ifstream& fIn, char(&field)[fieldWithИarriersSize][fieldWithИarriersSize], int& lowerSymbol, vector<pair<int, int>>& startFillPositions)
{
	char symbol;
	for (int i = 1; i < fieldWithИarriersSize - 1; i++)
	{
		for (int j = 1; j < fieldWithИarriersSize - 1; j++)
		{
			if (!fIn.get(symbol))break;
			if (symbol != '\n')
			{
				field[i][j] = symbol;
				if (symbol == 'O')
				{
					startFillPositions.push_back({ i, j });
				}
			}
			else
			{
				lowerSymbol = i;
				break;
			}
		}
	}
}


void WriteField(ofstream& fOut, char(&field)[fieldWithИarriersSize][fieldWithИarriersSize], int lowerSymbol)
{
	if (lowerSymbol == 0)
	{
		fOut << "\n";
		return;
	}
	for (int i = 1; i < fieldWithИarriersSize - 1; i++)
	{
		for (int j = 1; j < fieldWithИarriersSize - 1; j++)
		{
			fOut << field[i][j];
		}
		fOut << "\n";
		if (lowerSymbol == i)
		{
			break;
		}
	}
}


void FillField(ofstream &fOut, char(&field)[fieldWithИarriersSize][fieldWithИarriersSize], vector<pair<int, int>> const & startFillPositions, int& loweerSymbol)
{
	for (auto& startFillPosition : startFillPositions)
	{
		queue <pair<int, int>> q;//структура point
		q.push({ startFillPosition.first + 1, startFillPosition.second });
		q.push({ startFillPosition.first - 1, startFillPosition.second });
		q.push({ startFillPosition.first, startFillPosition.second + 1 });
		q.push({ startFillPosition.first, startFillPosition.second - 1 });
		pair<int, int> cell;
		while (!q.empty())
		{
			cell = q.front();
			q.pop();
			if (field[cell.first][cell.second] == ' ') {
				field[cell.first][cell.second] = '.';
				//дублирование кода
				q.push({ cell.first + 1, cell.second });
				q.push({ cell.first - 1, cell.second });
				q.push({ cell.first, cell.second + 1 });
				q.push({ cell.first, cell.second - 1 });
			}
			if (cell.first > loweerSymbol) loweerSymbol = cell.first;
		}
	}
}

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		cout << "Invalid argument count\n"
			<< "Usage: fill.exe <inputFile> <outputFile>\n";
		return 1;
	}
	//создать функцию для открывания файлов
	ifstream fIn(argv[1]);
	if (!fIn.is_open())
	{
		cout << "An error occurred opening the input file " << argv[1] << ".\nTry again.\n";
		return 1;
	}

	ofstream fOut(argv[2]);
	if (!fOut.is_open())
	{
		cout << "An error occurred opening the output file.\nTry again.\n";
		return 1;
	}

	char field[fieldWithИarriersSize][fieldWithИarriersSize]{};
	InitField(field);

	int lowerSymbol = 0;
	vector<pair<int, int>> startFillPositions;

	ReadField(fIn, field, lowerSymbol, startFillPositions);

	FillField(fOut, field, startFillPositions, lowerSymbol);

	WriteField(fOut, field, lowerSymbol);

	return 0;
}
