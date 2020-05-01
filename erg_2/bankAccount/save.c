#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define SIZE 5
#define UKNWOWN 5

int main()
{

    FILE *fp = fopen("pointValues.txt", "r");
    if (fp == NULL)
    {
        perror("Unable to open file!");
        exit(1);
    }

    char chunk[128];
    unsigned int points[10][2] = {};
    int iterator = 0;
    char *token;

    while (fgets(chunk, sizeof(chunk), fp) != NULL)
    {
        token = strtok(chunk, " ");
        points[iterator][0] = atoi(token);
        token = strtok(NULL, " ");
        points[iterator][1] = atoi(token);
        printf("%d ", points[iterator][0]);
        printf("%d\n", points[iterator][1]);
        iterator++;
    }

    fclose(fp);

    long double ratio, matrix[SIZE + 1][SIZE + 1];
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
                matrix[row][column] = points[row-1][1]; //-1 gia na ksekiname apo 0
                break;

            default:
                matrix[row][column] = points[row][0] * pow(points[row][0], (UKNWOWN - 1) - column); // row, row gia na ksekiname apoo 0
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