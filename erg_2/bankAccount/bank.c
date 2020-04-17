#include <stdio.h>
#include <limits.h>
#include <math.h>

int calculatePolynomial(int degree, int value, int password, int ai[])
{
    int coef;
    int calculation;

    value = password;

    for (coef = 0; coef < 4; coef++)
    {
        calculation = ai[coef] *pow(degree,coef+1);
        printf("----->%d\n",calculation);
        value += calculation;
    }

    return value;
}

int main()
{

    //ULONG_MAX
    int values[10] = {};
    int a0 = 23;
    int ai[8] = {2, 2, 3, 4};
    int point;

    point = calculatePolynomial(5,point,a0,ai);

    printf("%d\n",point);
}