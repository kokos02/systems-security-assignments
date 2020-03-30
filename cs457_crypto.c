#include "cs457_crypto.h"

int main()
{

    uint8_t plainText[] = TextInput;
    uint8_t *key;
    uint8_t *ciphertext;
    uint8_t *decrypted;
    int a = 20;

    key = getRandomkey();
    //showRandomKey_1(key);

    ciphertext = otp_encrypt(plainText, key);
    decrypted = otp_decrypt(ciphertext, key);
    //printf("%s\n",ciphertext);
    // showDecrypted_1(decrypted);
    //showEncrypted_1(ciphertext);
    // showRandomKey_1(key);

    // ciphertext = caesar_encrypt(plainText, 400);
    // //showEncrypted_1(ciphertext);
    // decrypted = caesar_decrypt(ciphertext, 400);
    // showDecrypted_1(decrypted);

    ciphertext = spartan_encrypt(plainText, a, SIZE_OF_TEXT);
     

    //decrypted = spartan_decrypt(ciphertext, a, strlen(ciphertext));
   // printf("%s\n", decrypted);
    //ciphertext = vigenere_encrypt(plainText,key);

    //decrypted = vigenere_decrypt(ciphertext,key);
    //printf("%s\n",decrypted);

    return 0;
}