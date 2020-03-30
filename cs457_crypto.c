#include "cs457_crypto.h"

int main()
{

    uint8_t plainText[] = TextInput;
    uint8_t *key;
    uint8_t *ciphertext;
    uint8_t *decrypted;
    int a=6;

    key = getRandomkey();
    ciphertext = otp_encrypt(plainText, key);
    decrypted = otp_decrypt(ciphertext, key);
    // showDecrypted_1(decrypted);
    // showEncrypted_1(ciphertext);
    // showRandomKey_1(key);

    ciphertext = caesar_encrypt(plainText, 4);
    //showEncrypted_1(ciphertext);
    decrypted = caesar_decrypt(ciphertext, 4);
    //showDecrypted_1(decrypted);

    //ciphertext = spartan_encrypt(plainText, a, SIZE_OF_TEXT);

    //decrypted =spartan_decrypt(ciphertext,a,strlen(ciphertext));

    ciphertext = vigenere_encrypt(plainText,plainText);

    return 0;
}