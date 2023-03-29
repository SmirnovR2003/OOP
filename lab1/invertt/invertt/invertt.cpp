// invertt.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>

using namespace std;

const int matrixSize = 3;

void WriteMatrix(double matrix[3][3]) 
{
    for (int i = 0; i < matrixSize; i++)
    {
        cout << matrix[i][0] << " " << matrix[i][1] << " " << matrix[i][2] << endl;
    }
}

void FirstStep(double(&matrix)[3][3], double(&invertedMatrix)[3][3])
{
    // приводим к единице matrix[0][0], обнуляем matrix[1][0] и matrix[2][0] 
    // и проводим соответствующие действия с остальными элементами матрицы
    if (matrix[0][0] == 0)
    {
        if (matrix[1][0] != 0)
        {
            for (int i = 0; i < matrixSize; i++)
            {
                swap(matrix[0][i], matrix[1][i]);
                swap(invertedMatrix[0][i], invertedMatrix[1][i]);
            }
        }
        else
        {
            for (int i = 0; i < matrixSize; i++)
            {
                swap(matrix[0][i], matrix[2][i]);
                swap(invertedMatrix[0][i], invertedMatrix[2][i]);
            }
        }
    }
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
}

void SecondStep(double(&matrix)[3][3], double(&invertedMatrix)[3][3])
{
    // приводим к единице matrix[1][1], обнуляем matrix[0][1] и matrix[2][1] 
    // и проводим соответствующие действия с остальными элементами матрицы
    if (matrix[1][1] == 0)
    {
        for (int i = 0; i < matrixSize; i++)
        {
            swap(matrix[1][i], matrix[2][i]);
            swap(invertedMatrix[1][i], invertedMatrix[2][i]);
        }
    }

    double divider1 = matrix[0][1];
    double divider2 = matrix[1][1];
    double divider3 = matrix[2][1];

    for (int i = 0; i < matrixSize; i++)
    {
        matrix[1][i] /= divider2;
        invertedMatrix[1][i] /= divider2;

        matrix[0][i] -= divider1 * matrix[1][i];
        invertedMatrix[0][i] -= divider1 * invertedMatrix[1][i];

        matrix[2][i] -= divider3 * matrix[1][i];
        invertedMatrix[2][i] -= divider3 * invertedMatrix[1][i];
    }
}

void ThirdStep(double(&matrix)[3][3], double(&invertedMatrix)[3][3])
{
    // приводим к единице matrix[2][2], обнуляем matrix[0][2] и matrix[1][2] 
    // и проводим соответствующие действия с остальными элементами матрицы
    double divider1 = matrix[0][2];
    double divider2 = matrix[1][2];
    double divider3 = matrix[2][2];

    for (int i = 0; i < matrixSize; i++)
    {
        matrix[2][i] /= divider3;
        invertedMatrix[2][i] /= divider3;

        matrix[0][i] -= divider1 * matrix[2][i];
        invertedMatrix[0][i] -= divider1 * invertedMatrix[2][i];

        matrix[1][i] -= divider2 * matrix[2][i];
        invertedMatrix[1][i] -= divider2 * invertedMatrix[2][i];
    }
}

void InvertMatrix(double (&matrix)[3][3], double (&invertedMatrix)[3][3])
{
    // приводим к единице matrix[0][0], обнуляем matrix[1][0] и matrix[2][0] 
    // и проводим соответствующие действия с остальными элементами матрицы
    FirstStep(matrix, invertedMatrix);

    // приводим к единице matrix[1][1], обнуляем matrix[0][1] и matrix[2][1] 
    // и проводим соответствующие действия с остальными элементами матрицы
    SecondStep(matrix, invertedMatrix);

    // приводим к единице matrix[2][2], обнуляем matrix[0][2] и matrix[1][2] 
    // и проводим соответствующие действия с остальными элементами матрицы
    ThirdStep(matrix, invertedMatrix);
}

int ReadMatrix(istream& fIn, double(&matrix)[3][3]) 
{

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

double FindMatrixDeterminant(double(&matrix)[3][3])
{
    return(matrix[0][0] * matrix[1][1] * matrix[2][2] +
        matrix[0][1] * matrix[1][2] * matrix[2][0] +
        matrix[0][2] * matrix[1][0] * matrix[2][1] -
        matrix[0][2] * matrix[1][1] * matrix[2][0] -
        matrix[0][1] * matrix[1][0] * matrix[2][2] - 
        matrix[0][0] * matrix[1][2] * matrix[2][1]);
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
    if(ReadMatrix(fIn, matrix)) 
    {
        cout << "Matrix reading error.\nCheck matrix in input file and try again.";
        return 1;
    }

    if (FindMatrixDeterminant(matrix) == 0)
    {
        cout << "It is impossible to find the inverse matrix since the determinant of the matrix is zero\n";
        return 1;
    }
    //создаем единичную матрицу для метода Гаусса
    double invertedMatrix[3][3]
    {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}
    };

    InvertMatrix(matrix, invertedMatrix);

    WriteMatrix(invertedMatrix);
}
