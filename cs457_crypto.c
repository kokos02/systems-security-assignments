#include "cs457_crypto.h"

int main()
{

    uint8_t plainText[] = "HelloWorld";
    uint8_t key[]="randombyte";
    uint8_t *ciphertext;
    uint8_t *decrypted;
    uint8_t *randomBytes;

    // key = malloc(SIZE_OF_TEXT * sizeof(uint8_t));
    // randomBytes = malloc(SIZE_OF_TEXT * sizeof(uint8_t));

    // printf("\n//////////////////////////////////////////////////");

    // getrandom(randomBytes, sizeof randomBytes, 0);
    // int y;
    // y = 0;
    // int success = 0;
    // while (y != 20000)
    // {
    //     if (isalpha(randomBytes[y]) || isdigit(randomBytes[y]))
    //     {
    //         key[success] = randomBytes[y];
    //         success++;
    //         if (success > SIZE_OF_TEXT)
    //         {
    //             break;
    //         }
    //     }

    //     y++;
    // }
    // y = 0;
    // while (y != SIZE_OF_TEXT)
    // {
    //     printf("----%c\n", key[y]);
    //     y++;
    // }

    ciphertext = otp_encrypt(plainText, key);
    decrypted = otp_decrypt(ciphertext, key);
    ShowDecrypted(decrypted);
    ShowEncrypted(ciphertext);

    return 0;
}