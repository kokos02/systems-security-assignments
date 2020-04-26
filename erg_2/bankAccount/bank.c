#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#define SIZE 11

#define UKNWOWN 9

int calculatePolynomial(int degree, int point, int password, int ai[])
{
    int coef;
    int calculation;

    point = password;

    for (coef = 0; coef < UKNWOWN-1; coef++)
    {
        calculation = ai[coef] * pow(degree + 1, coef + 1);
        point += calculation;
        //printf("----->%d\n", point);
    }
    printf("\n");
    return point;
}

int main()
{

    //ULONG_MAX
    int points[10] = {};
    int a0 = 23;
    int ai[8] = {2, 2, 3, 4, 2, 2, 3, 3};
    int point;
    int coef;

    for (coef = 0; coef < UKNWOWN; coef++)
    {
        points[coef] = calculatePolynomial(coef, point, a0, ai);
        printf("%d\n", points[coef]);
    }

    long double ratio, matrix[SIZE][SIZE], x[SIZE];
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
                matrix[row][column] = row * pow(row,(UKNWOWN-1)-column);
            }
            printf("%LF\n",matrix[row][column]);
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
        x[row] = x[row] / matrix[row][row];
    }
    /* Displaying Solution */
    printf("\nSolution:\n");
    for (row = 1; row <= UKNWOWN; row++)
    {
        printf("x[%d] = %LF\n", row, x[row]);
    }
}