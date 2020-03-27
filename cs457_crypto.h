#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sys/random.h>
#include <ctype.h>
#include <stdlib.h>

#define TextInput "HelloWorld"
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

void ShowEncrypted(uint8_t *encrypted)
{
    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("%x\n", encrypted[count]);
        count++;
    }
}

void ShowDecrypted(uint8_t *decrypted)
{
    int count = 0;
    while (count != SIZE_OF_TEXT)
    {
        printf("%c\n", decrypted[count]);
        count++;
    }
}
