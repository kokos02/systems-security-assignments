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


unsigned long long int  calculatePolynomial(int degree, unsigned long long int  point, int password, unsigned int ai[])
{
    unsigned long coef;
    unsigned long calculation;

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

    printf("%u\n", randomNumber);

    return randomNumber;
}

int main()
{

    //ULONG_MAX
    unsigned long long int  points[10] = {};
    int  a0 = 23;
    unsigned int ai[8] = {};
    unsigned long long int  point;
    int coef;

    for (int coef = 0; coef < 8; coef++)
    {
        ai[coef] = getRandomkey();
        printf("%u\n", ai[coef]);
    }

    for (coef = 0; coef < 10; coef++)
    {
        points[coef] = calculatePolynomial(coef, point, a0, ai);
        printf("%llu\n", points[coef]);
    }
}