/*Вариант 11.
Написать программу, которая создает динамическую матрицу размерности
A[n*n], элементы матрицы А – целые числа, заданные случайным образом. Найти строки, среди элементов которых есть
отрицательные элементы.
Изменить порядок строк матрицы: отсортировать строки матрицы по убыванию максимальных
элементов строк. Использовать сортировку вставками.*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int* arr, int size)
{
    for (int i = 1; i < size; i++)
    {
        int centralValue = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] < centralValue)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = centralValue;
    }
}

void sortNegativeRows(int** matrix, int row, int column)
{
    int* tempMatrix = (int*)malloc(column * sizeof(int)); //временное  хранилище 
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (matrix[i][j] < 0)
            {
                for (int k = 0; k < column; k++)
                {
                    tempMatrix[k] = matrix[i][k];
                }
                insertionSort(tempMatrix, column);
                for (int k = 0; k < column; k++)
                {
                    matrix[i][k] = tempMatrix[k];
                }
                free(tempMatrix);
            }
        }
    }
}

void swapRows(int** matrix, int i, int j, int column)
{
    for (int k = 0; k < column; k++)
    {
        int temp = matrix[i][k];
        matrix[i][k] = matrix[j][k];
        matrix[j][k] = temp;
    }
}

void sortRows(int** matrix, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = i + 1; j < row; j++)
        {
            if (findMax(matrix, row, column) == findMax(matrix, j, column))
            {
                swapRows(matrix, i, j, column);
            }
        }
    }
}

int findMax(int** matrix, int row, int column)
{
    int max = matrix[0][0];
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (matrix[i][j] > max)
                max = matrix[i][j];
        }
    }
    return max;
}

void error()
{
    printf("Вы все сломали. В следующий раз вводите корректные значения.");
    exit(1);
}

int main()
{
    system("chcp 1251");
    int dimensity;
    printf("Введите размерность матрицы:\t");
    int isdigit = scanf_s("%d", &dimensity);
    if (isdigit != 1)
        error();

    int row, column;
    //матрица квадратная
    row = dimensity; 
    column = dimensity;
    int** matrix = (int**)malloc(row * sizeof(int*));
    for (int i = 0; i < row; i++)
        matrix[i] = (int*)malloc(column * sizeof(int));

    srand(time(0));
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            matrix[i][j] = rand() % 20 - 10;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    sortNegativeRows(matrix, row, column);

    printf("\nSorted matrix:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    sortRows(matrix, row, column);

    printf("\nMatrix with rows sorted in descending order of maximum row elements:\n");
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    return 0;
}
