#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

void sort(int** matrix, int* keys, int dimensity)
{
    for (int i = 0; i < dimensity - 1; ++i)
    {
        int max = i;
        for (int j = i + 1; j < dimensity; ++j)
        {
            if (keys[j] > keys[max])
            {
                max = j;
            }
        }
        if (max != i)
        {
            int* tmp = matrix[max];
            matrix[max] = matrix[i];
            matrix[i] = tmp;
            int tmp_key = keys[max];
            keys[max] = keys[i];
            keys[i] = tmp_key;
        }
    }
}

void print(int dimensity, int** matrix)
{
    for (int i = 0; i < dimensity; i++)
    {
        for (int j = 0; j < dimensity; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    SetConsoleOutputCP(1251);

    //создание динамической матрицы размерности A[n * n]
    int dimensity;
    printf("Введите размерность матрицы: ");
    int isDigit = scanf_s("%d", &dimensity);
    if (isDigit != 1)
    {
        printf("Вы все сломали. В следующий раз вводите корректные значения.");
        exit(1);
    }
    int** matrix = (int**)malloc(dimensity * sizeof(int*));

    //Заполнение матрицы А целыми числами, заданными случайным образом
    srand(time(0));
    for (int i = 0; i < dimensity; i++)
    {
        matrix[i] = (int*)malloc(dimensity * sizeof(int));
        for (int j = 0; j < dimensity; j++)
        {
            matrix[i][j] = rand() % 20 - 10;
        }
    }

    //Вывод исходной матрицы
    printf("\nИсходная матрица:\n");
    print(dimensity, matrix);

    //Поиск строк с отрицательными элементами
    int* zero_rows = (int*)malloc(dimensity * sizeof(int));
    for (int i = 0; i < dimensity; i++)
    {
        for (int j = 0; j < dimensity; j++)
        {
            if (matrix[i][j] < 0)
            {
                zero_rows[i] = 1;
                break;
            }
        }
    }

    printf("\nИндексы строк, содержащих отрицательные значения:");
    for (int i = 0; i < dimensity; i++)
    {
        if (zero_rows[i] == 1)
        {
            printf("\t%d", i);
        }
    }

    //Поиск максимальных элементов в строках
    int* max = (int*)malloc(dimensity * sizeof(int));
    for (int i = 0; i < dimensity; i++)
    {
        max[i] = matrix[i][0];
        for (int j = 1; j < dimensity; j++)
        {
            if (matrix[i][j] > max[i])
            {
                max[i] = matrix[i][j];
            }
        }
    }

    //сортировка строк матрицы по убыванию максимальных элементов строк
    sort(matrix, max, dimensity);
    printf("\n\nСортированная матрица:\n");
    print(dimensity, matrix);
    _getch();
    free(matrix);
    free(max);
    free(zero_rows);
    return 0;
}