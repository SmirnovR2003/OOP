// invertt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

const int matrixSize = 3;

void writeMatrix(double matrix[3][3]) 
{

    for (int i = 0; i < matrixSize; i++)
    {
        cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << endl;
    }
}

void invertMatrix(double (&matrix)[3][3], double (&invertedMatrix)[3][3])
{
    // приводим к единице matrix[0][0], обнуляем matrix[1][0] и matrix[2][0] 
    // и проводим соответствующие действия с остальными элементами матрицы
#pragma region FirstStep 

    double divider1 = matrix[0][0];
    double divider2 = matrix[1][0];
    double divider3 = matrix[2][0];


    for (int i = 0; i < matrixSize; i++)
    {
        matrix[0][i] /= divider1;
        invertedMatrix[0][i] /= divider1;

        matrix[1][i] -= divider2 * matrix[0][i];
        invertedMatrix[1][i] -= divider2 * invertedMatrix[0][i];

        matrix[2][i] -= divider3 * matrix[0][i];
        invertedMatrix[2][i] -= divider3 * invertedMatrix[0][i];
    }
#pragma endregion 

    // приводим к единице matrix[1][1], обнуляем matrix[0][1] и matrix[2][1] 
    // и проводим соответствующие действия с остальными элементами матрицы
#pragma region SecondStep


    divider1 = matrix[0][1];
    divider2 = matrix[1][1];
    divider3 = matrix[2][1];

    for (int i = 0; i < matrixSize; i++)
    {

        matrix[1][i] /= divider2;
        invertedMatrix[1][i] /= divider2;

        matrix[0][i] -= divider1 * matrix[1][i];
        invertedMatrix[0][i] -= divider1 * invertedMatrix[1][i];

        matrix[2][i] -= divider3 * matrix[1][i];
        invertedMatrix[2][i] -= divider3 * invertedMatrix[1][i];
    }

#pragma endregion

    // приводим к единице matrix[2][2], обнуляем matrix[0][2] и matrix[1][2] 
    // и проводим соответствующие действия с остальными элементами матрицы
#pragma region ThirdStep

    divider1 = matrix[0][2];
    divider2 = matrix[1][2];
    divider3 = matrix[2][2];

    for (int i = 0; i < matrixSize; i++)
    {
        matrix[2][i] /= divider3;
        invertedMatrix[2][i] /= divider3;

        matrix[0][i] -= divider1 * matrix[2][i];
        invertedMatrix[0][i] -= divider1 * invertedMatrix[2][i];

        matrix[1][i] -= divider2 * matrix[2][i];
        invertedMatrix[1][i] -= divider2 * invertedMatrix[2][i];

    }

#pragma endregion
}

int ReadMatrix(ifstream& fIn, double(&matrix)[3][3]) {

    for (int i = 0; i < matrixSize; i++)
    {
        for (int j = 0; j < matrixSize; j++)
        {
            if (!(fIn >> matrix[i][j]))
            {
                return 1;
            };
        }
    }
    return 0;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "Invalid argument count\nUsage: <inputFile>\n";
        return 1;
    }

    ifstream fIn(argv[1]);
    if (!fIn.is_open()) 
    {
        cout << "An error occurred opening the input file.\nTry again.";
        return 1;
    }

    double matrix[3][3]
    {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };
    //считываем матрицу
    if(ReadMatrix(fIn, matrix) == 1) 
    {
        cout << "Matrix reading error.\nCheck matrix in input file and try again.";
        return 1;
    }
    //создаем единичную матрицу
    double invertedMatrix[3][3]
    {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    invertMatrix(matrix, invertedMatrix);
    writeMatrix(invertedMatrix);
}
