#include <stdio.h>
#include <limits.h>
#include <math.h>

int calculatePolynomial(int degree, int point, int password, int ai[])
{
    int coef;
    int calculation;

    point = password;

    for (coef = 0; coef < 4; coef++)
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

    for (coef = 0; coef < 5; coef++)
    {
        points[coef] = calculatePolynomial(coef, point, a0, ai);
        printf("%d\n", points[coef]);
    }
}