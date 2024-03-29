#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define TextInput "ATTACKATDAWN"
#define SIZE_OF_TEXT strlen(TextInput)
#define LENGTH_OF_ALPHABET 26
#define A_ON_ASCII 65

uint8_t *otp_encrypt(uint8_t *plaintext, uint8_t *key)
{
    int counter;
    uint8_t *encrypted;
    uint8_t currentCharacter;
    counter = 0;

    encrypted = (uint8_t *)malloc(SIZE_OF_TEXT * sizeof(uint8_t*));

    while (counter != SIZE_OF_TEXT)
    {
        currentCharacter = plaintext[counter] ^ key[counter]; // we xor each character of the plain text with the corresponding character from the key
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

    decrypted = (uint8_t *)malloc(SIZE_OF_TEXT * sizeof(uint8_t*));

    while (count != SIZE_OF_TEXT)
    {
        currentCharacter = ciphertext[count] ^ key[count]; // to decrypt we xor each character of the ciphertext with the corresponding from the key
        decrypted[count] = currentCharacter;
        count++;
    }

    return decrypted;
}

uint8_t *getRandomkey()
{

    uint8_t *key;

    key = (uint8_t *)malloc(SIZE_OF_TEXT * sizeof(uint8_t*));

    int randomData = open("/dev/urandom", O_RDONLY);

    if (randomData < 0)
    {
        printf("something went wrong\n");
        exit(1);
    }
    else
    {
        char myRandomData[50];
        ssize_t result = read(randomData, key, sizeof myRandomData);
        if (result < 0)
        {
            printf("something went wrong\n");
            exit(1);
        }
    }

    return key;
}

void showEncryptedOtp(uint8_t *encrypted) //function to show the result of the otp encrypt
{
    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("%x", encrypted[count]);
        count++;
    }
    printf("\n");
}

void showDecryptedOtp(uint8_t *decrypted) //function to show the result of the otp decrypt
{
    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("%c", decrypted[count]);
        count++;
    }
    printf("\n");
}

uint8_t *caesar_encrypt(uint8_t *plaintext, ushort N)
{
    uint8_t *encrypted;
    int count = 0;

    encrypted = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t*));
    strcpy(encrypted, plaintext);

    while (count != SIZE_OF_TEXT) // Loop through the plain text
    {
        int nestedCount = 0;

        while (nestedCount != N) // for each character we change the value N times and check if we overflow the alphabet or the numbers
        {

            switch (encrypted[count])
            {
            case 'Z':
                encrypted[count] = 'A';
                nestedCount++;
                break;
            case 'z':
                encrypted[count] = 'a';
                nestedCount++;
                break;
            case '9':
                encrypted[count] = '0';
                nestedCount++;
                break;
            default:
                encrypted[count]++;
                nestedCount++;
            }
        }
        count++;
    }

    return encrypted; // return the encrypted plain text
}

uint8_t *caesar_decrypt(uint8_t *ciphertext, ushort N)
{
    uint8_t *decrypted;
    int count = 0;

    decrypted = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t*));
    strcpy(decrypted, ciphertext);

    while (count != SIZE_OF_TEXT) // Loop through the plain text
    {
        int nestedCount = N;

        while (nestedCount != 0) // for each character we change the value N times and check if we overflow the alphabet or the numbers
        {

            switch (decrypted[count])
            {
            case 'A':
                decrypted[count] = 'Z';
                nestedCount--;
                break;
            case 'a':
                decrypted[count] = 'z';
                nestedCount--;
                break;
            case '0':
                decrypted[count] = '9';
                nestedCount--;
                break;
            default:
                decrypted[count]--;
                nestedCount--;
            }
        }

        count++;
    }

    return decrypted; // return the decrypted text
}

uint8_t *spartan_encrypt(uint8_t *plaintext, int circ, int len)
{

    uint8_t *encrypted;
    uint8_t *text;
    int loopCount = 0, iterator = 0, shouldGoBack;
    bool endFlag = false;
    int toAdd = 0, checkIfHashNeeded;

    checkIfHashNeeded = len % circ;

    if (checkIfHashNeeded != 0)
    {
        toAdd = len - (len - (circ - checkIfHashNeeded));
    }

    text = (uint8_t *)calloc((SIZE_OF_TEXT + toAdd), sizeof(uint8_t*));
    strcpy(text, plaintext);
    if (checkIfHashNeeded != 0)
    {
        int count;

        for (count = 1; count < toAdd + 1; count++)
        {
            text[len + count - 1] = '#';
        }
    }

    encrypted = (uint8_t *)calloc((SIZE_OF_TEXT + toAdd), sizeof(uint8_t *));

    encrypted[SIZE_OF_TEXT + toAdd - 1] = '!'; //last element indicator
    encrypted[SIZE_OF_TEXT + toAdd] = '\0';

    while (endFlag == false)
    {

        while (text[iterator] == '!')
        {
            iterator++;
        }

        encrypted[loopCount] = text[iterator];

        text[iterator] = '!'; // we put an ! in each cell we used so we wno't use it again

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
    uint8_t *decrypted;
    int loopCount = 0, iterator = 0, shouldGoBack;
    bool endFlag = false;
    int toAdd = 0, checkIfHashNeeded;
    int step;
    step = strlen(ciphertext) / circ;

    decrypted = (uint8_t *)malloc((len) * sizeof(uint8_t *));

    decrypted[len - 1] = '!'; //last element indicator
    decrypted[len] = '\0';

    while (endFlag == false)
    {
        while (ciphertext[iterator] == '!')
        {
            iterator++;
        }

        decrypted[loopCount] = ciphertext[iterator];

        ciphertext[iterator] = '!'; // we put an ! in each cell we used so we wno't use it again

        loopCount++;
        iterator += step;                    // we go to the next letter to put on the chiper
        shouldGoBack = (len - 1) - iterator; // check if we overlow the plain text
        if (shouldGoBack <= 0)               // if so we go the iterator back to the begining
        {
            iterator = -shouldGoBack;
        }
        if (decrypted[len - 1] != '!')
        {
            endFlag = true;
        }
    }
    return decrypted;
}

uint8_t *vigenere_encrypt(uint8_t *plaintext, uint8_t *key)
{
    uint8_t alphaTable[26][26], currentLetter;
    int iteratorRow, iteratorCol, iterator;
    int position = 0;
    uint8_t *encrypted;
    uint8_t *error;

    encrypted = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t*));
    encrypted = plaintext;
    while (position != SIZE_OF_TEXT)
    {
        if (!isupper(encrypted[position]) || !isupper(key[position]))
        {
            error = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t*));
            printf("Only CAPITAL letters please!!! Exiting....\n");
            return error;
        }
        position++;
    }

    for (iteratorRow = 0; iteratorRow < LENGTH_OF_ALPHABET; iteratorRow++)
    {
        currentLetter = 'A' + iteratorRow; // Startin from A for each row we move +rowIndex to next lettter
        for (iteratorCol = 0; iteratorCol < LENGTH_OF_ALPHABET; iteratorCol++)
        {
            if (iteratorCol != 0) // if we are not on the first column we go to the next letter
            {
                currentLetter += 1;
            }

            if (currentLetter > 'Z') // if we reach the end of the alphabet we restart
            {
                currentLetter = 'A';
            }
            alphaTable[iteratorRow][iteratorCol] = currentLetter;
        }
    }

    for (iterator = 0; iterator < SIZE_OF_TEXT; iterator++)
    {
        encrypted[iterator] = alphaTable[encrypted[iterator] - A_ON_ASCII][key[iterator] - A_ON_ASCII]; // we subtract the A on ascii so we get the actual index of the letter in the alphabet
    }

    return encrypted;
}

uint8_t *vigenere_decrypt(uint8_t *ciphertext, uint8_t *key)
{
    uint8_t alphaTable[26][26], currentLetter;
    int iteratorRow, iteratorCol, iterator;
    int position = 0;
    uint8_t *error;

    while (position != SIZE_OF_TEXT)
    {
        if (!isupper(ciphertext[position]) || !isupper(key[position]))
        {
            error = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t*));
            printf("Only CAPITAL letters please!!! Exiting....\n");
            return error;
        }
        position++;
    }

    for (iteratorRow = 0; iteratorRow < LENGTH_OF_ALPHABET; iteratorRow++)
    {
        currentLetter = 'A' + iteratorRow; // Starting from A for each row we move +rowIndex to next lettter
        for (iteratorCol = 0; iteratorCol < LENGTH_OF_ALPHABET; iteratorCol++)
        {
            if (iteratorCol != 0) // if we are not on the first column we go to the next letter
            {
                currentLetter += 1;
            }

            if (currentLetter > 'Z') // if we reach the end of the alphabet we restart
            {
                currentLetter = 'A';
            }
            alphaTable[iteratorRow][iteratorCol] = currentLetter;
        }
    }

    for (iterator = 0; iterator < SIZE_OF_TEXT; iterator++)
    {
        int index = 0;
        while (alphaTable[key[iterator] - A_ON_ASCII][index] != ciphertext[iterator])
        {
            index++;
        }
        ciphertext[iterator] = alphaTable[0][index];
    }

    return ciphertext;
}