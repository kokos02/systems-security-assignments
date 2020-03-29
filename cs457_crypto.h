#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/random.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

#define TextInput "Iamhurtverybadlyhelp"
#define SIZE_OF_TEXT strlen(TextInput)

uint8_t *otp_encrypt(uint8_t *plaintext, uint8_t *key)
{
    int counter;
    uint8_t *encrypted;
    uint8_t currentCharacter;
    counter = 0;

    encrypted = malloc(SIZE_OF_TEXT * sizeof(uint8_t));

    while (counter != SIZE_OF_TEXT)
    {
        currentCharacter = plaintext[counter] ^ key[counter];
        encrypted[counter] = currentCharacter;
        counter++;
    }
    return encrypted;
}

uint8_t *otp_decrypt(uint8_t *ciphertext, uint8_t *key)
{
    int count = 0;
    uint8_t currentCharacter;
    uint8_t *decrypted;

    decrypted = malloc(SIZE_OF_TEXT * sizeof(uint8_t));

    while (count != SIZE_OF_TEXT)
    {
        currentCharacter = ciphertext[count] ^ key[count];
        decrypted[count] = currentCharacter;
        count++;
    }

    return decrypted;
}

uint8_t *getRandomkey()
{
    uint8_t randomBytes[200] = {}; // 200 is a random big number so we are sure we get enough letters and numbers
    uint8_t *key;
    int count = 0;
    int success = 0;

    key = malloc(SIZE_OF_TEXT * sizeof(uint8_t));

    getrandom(randomBytes, sizeof randomBytes, 0); // puts random bytes into randomBytes

    while (count != 150)
    {

        if (isalpha(randomBytes[count]) || isdigit(randomBytes[count])) // if it's a number or a letter we give it to the key
        {
            key[success] = randomBytes[count];
            success++;
            if (success > SIZE_OF_TEXT)
            {
                break;
            }
        }
        count++;
    }

    return key;
}

void showRandomKey_1(uint8_t *key)
{

    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("==%c==\n", key[count]);
        count++;
    }
}

void showEncrypted_1(uint8_t *encrypted)
{
    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("%c\n", encrypted[count]);
        count++;
    }
}

void showDecrypted_1(uint8_t *decrypted)
{
    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("%c\n", decrypted[count]);
        count++;
    }
}

uint8_t *caesar_encrypt(uint8_t *plaintext, ushort N)
{

    int count = 0;

    while (count != SIZE_OF_TEXT) // Loop through the plain text
    {
        int nestedCount = 0;

        while (nestedCount != N) // for each character we change the value N times and check if we overflow the alphabet or the numbers
        {

            switch (plaintext[count])
            {
            case 'Z':
                plaintext[count] = 'A';
                nestedCount++;
                break;
            case 'z':
                plaintext[count] = 'a';
                nestedCount++;
                break;
            case '9':
                plaintext[count] = '0';
                nestedCount++;
                break;
            default:
                plaintext[count]++;
                nestedCount++;
            }
        }
        count++;
    }

    return plaintext; // return the encrypted plain text
}

uint8_t *caesar_decrypt(uint8_t *ciphertext, ushort N)
{

    int count = 0;

    while (count != SIZE_OF_TEXT) // Loop through the plain text
    {
        int nestedCount = N;

        while (nestedCount != 0) // for each character we change the value N times and check if we overflow the alphabet or the numbers
        {

            switch (ciphertext[count])
            {
            case 'A':
                ciphertext[count] = 'Z';
                nestedCount--;
                break;
            case 'a':
                ciphertext[count] = 'z';
                nestedCount--;
                break;
            case '0':
                ciphertext[count] = '9';
                nestedCount--;
                break;
            default:
                ciphertext[count]--;
                nestedCount--;
            }
        }

        count++;
    }

    return ciphertext; // return the decrypted text
}

uint8_t *spartan_encrypt(uint8_t *plaintext, ushort circ, ushort len)
{

    uint8_t *encrypted;
    int loopCount = 0, iterator = 0, shouldGoBack;
    bool endFlag = false;
    int toAdd = 0, checkIfHashNeeded;
    uint8_t terminationChar = '\0';

    checkIfHashNeeded = len % circ;
    if (checkIfHashNeeded != 0)
    {
        int count;

        toAdd = len - (len - (circ - checkIfHashNeeded));

        for (count = 1; count < toAdd + 1; count++)
        {
            plaintext[len + count - 1] = '#';
        }

        len += toAdd;
    }

    encrypted = (uint8_t *)malloc((SIZE_OF_TEXT) * sizeof(uint8_t));

    encrypted[SIZE_OF_TEXT + toAdd - 1] = '!'; //last element indicator
    encrypted[SIZE_OF_TEXT + toAdd] = '\0';

    while (endFlag == false)
    {
        while (plaintext[iterator] == '!')
        {
            iterator++;
        }

        encrypted[loopCount] = plaintext[iterator];
        plaintext[iterator] = '!'; // we put an ! in each cell we used so we wno't use it again

        loopCount++;
        iterator += circ;                                     // we go to the next letter to put on the chiper
        shouldGoBack = (SIZE_OF_TEXT + toAdd - 1) - iterator; // check if we overlow the plain text
        if (shouldGoBack <= 0)                                // if so we go the iterator back to the begining
        {
            iterator = -shouldGoBack;
        }
        if (encrypted[SIZE_OF_TEXT + toAdd - 1] != '!')
        {
            endFlag = true;
        }
    }

    return encrypted;
}

uint8_t *spartan_decrypt(uint8_t *ciphertext, ushort circ, ushort len)
{
}