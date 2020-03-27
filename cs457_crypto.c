#include "cs457_crypto.h"

int main()
{

    uint8_t plainText[] = "HelloWorld";
    uint8_t *key;
    uint8_t *ciphertext;
    uint8_t *decrypted;


    key = getRandomkey();
    ciphertext = otp_encrypt(plainText, key);
    decrypted = otp_decrypt(ciphertext, key);
    // showDecrypted(decrypted);
    // showEncrypted(ciphertext);
    // showRandomKey(key);

    return 0;
}