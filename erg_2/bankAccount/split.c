#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#define SIZE 10

#define UKNWOWN 5

int calculatePolynomial(int degree, int point, int password, uint8_t ai[])
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

unsigned int getRandomkey()
{
    unsigned int randomNumber;
    FILE *f;

    f = fopen("/dev/random", "r");
    fread(&randomNumber, sizeof(unsigned int), 1, f);
    fclose(f);

    printf("%d\n", randomNumber);

    return randomNumber;
}

int main()
{

    //ULONG_MAX
    int points[10] = {};
    int a0 = 23;
    unsigned int ai[8] = {};
    int point;
    int coef;

    for (int coef = 0; coef < 8; coef++)
    {
        ai[coef] = getRandomkey();
        printf("%u\n", ai[coef]);
    }

    for (coef = 0; coef < 5; coef++)
    {
        points[coef] = calculatePolynomial(coef, point, a0, ai);
        printf("%d\n", points[coef]);
    }
}