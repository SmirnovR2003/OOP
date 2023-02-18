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

void ReadField(ifstream& fIn, char(&field)[fieldWithИarriersSize][fieldWithИarriersSize], int& lowerSymbol, vector<pair<int, int>>& positions)
{
	char symbol;
	for (int i = 1; i < fieldWithИarriersSize - 1; i++)
	{
		for (int j = 1; j < fieldWithИarriersSize - 1; j++)
		{
			if(fIn.get(symbol))
				lowerSymbol = i;
			if (symbol != '\n')
			{
				field[i][j] = symbol;
				if (symbol == 'O')
				{
					positions.push_back({ i, j });
				}
			}
			else
			{
				break;
			}
		}
	}
}

void WriteField(ofstream& fOut, char(&field)[fieldWithИarriersSize][fieldWithИarriersSize], int& lowerSymbol)
{
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


void FillField(ofstream &fOut, char(&field)[fieldWithИarriersSize][fieldWithИarriersSize], vector<pair<int, int>> positions, int& loweerSymbol)
{
	int a = 100;
	for (auto& position : positions)
	{
		queue <pair<int, int>> q;
		q.push({ position.first + 1, position.second });
		q.push({ position.first - 1, position.second });
		q.push({ position.first, position.second + 1 });
		q.push({ position.first, position.second - 1 });
		pair<int, int> cell;
		while (!q.empty())
		{
			cell = q.front();
			q.pop();
			if (field[cell.first][cell.second] == ' ') {
				field[cell.first][cell.second] = '.';
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
	int lowerSymbol = 0;
	vector<pair<int, int>> positions;

	InitField(field);

	ReadField(fIn, field, lowerSymbol, positions);

	FillField(fOut, field, positions, lowerSymbol);

	WriteField(fOut, field, lowerSymbol);

	return 0;
}
