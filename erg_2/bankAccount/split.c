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

unsigned long long int calculatePolynomial(int degree, unsigned long long int point, int password, unsigned char ai[])
{
    unsigned long coef;
    unsigned long calculation;

    point = password;

    for (coef = 0; coef < 8; coef++)
    {
        calculation = ai[coef] * pow(degree + 1, coef + 1);
        point += calculation;
    }
    return point;
}

unsigned char getRandomkey()
{
    unsigned char randomNumber;
    FILE *f;

    f = fopen("/dev/urandom", "r");
    fread(&randomNumber, sizeof(unsigned char), 1, f);
    fclose(f);

    return randomNumber;
}

int main()
{
    unsigned long long int points[10] = {};
    int a0 = 23;
    unsigned char ai[8] = {1,1,1,1,1,1,1,1};
    unsigned long long int point;
    int coef;
    FILE *pointValues;

    // for (coef = 0; coef < 8; coef++)
    // {
    //     ai[coef] = getRandomkey();
    //     while ((coef == 5 || coef == 6 || coef == 7) && ai[coef] > 20)
    //     {
    //         printf("again--->%u\n", ai[coef]);
    //         ai[coef] = getRandomkey();
    //     }
    //     printf("%u\n", ai[coef]);
    // }
    printf("the polyonim is: ");
    printf("%d*X^8+ ", ai[7]);
    for (coef = 6; coef >= 0; coef--)
    {
        printf("%d*X^%d+ ", ai[coef], coef + 1);
    }
    printf("%d\n", a0);

    for (coef = 0; coef < 10; coef++)
    {
        points[coef] = calculatePolynomial(coef, point, a0, ai);
        printf("%llu\n", points[coef]);
    }

    

    pointValues = fopen("pointValues.txt", "w");
    //    fprintf(pointValues, "This is testing for fprintf...\n");
    //    fputs("This is testing for fputs...\n", pointValues);
    for (coef = 0; coef < 10; coef++)
    {
        fprintf(pointValues, "%llu\n", points[coef]);
    }
    
    fclose(pointValues);
}