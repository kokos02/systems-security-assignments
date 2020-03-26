#include <stdio.h>
#include <string.h> 
#include <stdint.h>
#include <sys/random.h>
#include <ctype.h>

int main()
{
    uint8_t  plainText[] = "HelloWorld";
    uint8_t  key[] = "randombyte";
    int y = 0;
    uint8_t rendomBytes[140] = {};
    uint8_t decrypted[40] = {};
    uint8_t encrypted[80] = {};
    uint8_t currentCharacter;
    char gap = ' ';
    

    // printf("\n\n================================");

    // printf("\n\n================================");

    while (y != 10)
    {
        printf("\n\n================================");
        currentCharacter = plainText[y]^key[y];
        encrypted[y] = currentCharacter;
        //strncat(encrypted, &gap, 1);
        //strncat(encrypted, &currentCharacter, 1);
        printf("\n%c \n",encrypted[y]);
        y++;
        printf("\n\n================================");
    }

    printf("\n\n\n\n\n");

    y=0;

    while (y != 10)
    {
        currentCharacter = encrypted[y]^key[y];
        decrypted[y] = currentCharacter;
        printf("%x \n",decrypted[y]);
        y++;
    }
    printf("\n//////////////////////////////////////////////////");
   int r = getrandom(rendomBytes, sizeof rendomBytes, 0);
    y=0;
    int success =0;
    while (y != 140)
    {
        if (isalpha(rendomBytes[y]) || isdigit(rendomBytes[y]))
        {
            encrypted[success] = rendomBytes[y];
            success++;
        }

        y++;
    }
    y=0;
    while (y != 40)
    {
        printf("****** \n%c \n",encrypted[y]);
    y++;
    }
    
    
    
    

    return 0;
}