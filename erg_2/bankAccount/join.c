#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 11
#define UKNWOWN 9

int main()
{

    FILE *fp = fopen("pointValues.txt", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    char chunk[128];
    unsigned int points[10] = {};
    int iterator = 0;

    while (fgets(chunk, sizeof(chunk), fp) != NULL)
    {
        points[iterator] = atoi(chunk);
        printf("%d\n", points[iterator]);
        iterator++;
    }

    fclose(fp);

    long double ratio, matrix[SIZE][SIZE];
    double x[SIZE], temp;
    int row, column, k;

    /* 2. Reading Augmented Matrix */
    for (row = 1; row <= UKNWOWN; row++)
    {
        for (column = 1; column <= UKNWOWN + 1; column++)
        {
            printf("matrix[%d][%d] = ", row, column);

            switch (column)
            {
            case UKNWOWN:
                matrix[row][column] = 1;
                break;

            case UKNWOWN + 1:
                matrix[row][column] = points[row - 1];
                break;

            default:
                matrix[row][column] = row * pow(row, (UKNWOWN - 1) - column);
            }
            printf("%LF\n", matrix[row][column]);
        }
    }
    /* Applying Gauss Elimination */
    for (row = 1; row <= UKNWOWN - 1; row++)
    {
        if (matrix[row][row] == 0)
        {
            printf("Mathematical Error!\n");
            exit(0);
        }
        for (column = row + 1; column <= UKNWOWN; column++)
        {
            ratio = matrix[column][row] / matrix[row][row];

            for (k = 1; k <= UKNWOWN + 1; k++)
            {
                matrix[column][k] = matrix[column][k] - ratio * matrix[row][k];
            }
        }
    }
    /* Obtaining Solution by Back Subsitution */
    x[UKNWOWN] = matrix[UKNWOWN][UKNWOWN + 1] / matrix[UKNWOWN][UKNWOWN];

    for (row = UKNWOWN - 1; row >= 1; row--)
    {
        x[row] = matrix[row][UKNWOWN + 1];
        for (column = row + 1; column <= UKNWOWN; column++)
        {
            x[row] = x[row] - matrix[row][column] * x[column];
        }
        temp = x[row] / matrix[row][row];
        x[row] = temp;
    }
    /* Displaying Solution */
    printf("\nSolution:\n");
    for (row = 1; row <= UKNWOWN; row++)
    {
        printf("x[%d] = %f\n", row, (x[row]));
    }
}