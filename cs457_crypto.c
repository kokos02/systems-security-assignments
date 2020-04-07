#include "cs457_crypto.h"

int main()
{

    uint8_t plainText[] = TextInput;
    uint8_t key[] = "LEMONLEMONLE";
    uint8_t *randomKey;
    uint8_t *ciphertext;
    uint8_t *encrypted;
    uint8_t *decrypted;

    /*==========Uncomment this block to check the otp encrypt, assign your plaintext on the TextInput 
    //macro on the header file.============================================
    randomKey = getRandomkey();
    ciphertext = otp_encrypt(plainText, randomKey);
    decrypted = otp_decrypt(ciphertext, randomKey);
    showEncryptedOtp(ciphertext);
    showDecryptedOtp(decrypted);
    */
   

    /*=========Uncomment this block to check the ceasar encrypt, assign your plaintext on the TextInput 
    //macro on the header file.============================================

    // encrypted = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t));
    ciphertext = caesar_encrypt(plainText, 4);
    // strcpy(encrypted, ciphertext);
    decrypted = caesar_decrypt(ciphertext, 4);
    printf("%s\n", ciphertext);
    printf("%s\n", decrypted);
    */


    /*=========Uncomment this block to check the spartan encrypt, assign your plaintext on the TextInput 
    //macro on the header file.============================================*/

    //encrypted = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t));
    ciphertext = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t));
    //strcpy(ciphertext,spartan_encrypt(plainText, 6, SIZE_OF_TEXT));
    ciphertext = spartan_encrypt(plainText, 5, SIZE_OF_TEXT);
    //strcpy(encrypted, ciphertext);
    printf("%s\n", ciphertext);
    decrypted = spartan_decrypt(ciphertext, 5, strlen(ciphertext));
    printf("%s\n", decrypted);
    


    /*=======Uncomment this block to check the vigenere encrypt, assign your plaintext on the TextInput 
    //macro on the header file and the key at the top of the main.. Only CAPITAL LETTERS PLEASE!!!==========

    ciphertext = (uint8_t *)calloc((SIZE_OF_TEXT), sizeof(uint8_t));
    ciphertext = vigenere_encrypt(plainText, key);
    //strcpy(ciphertext, vigenere_encrypt(plainText, key));
    printf("%s\n", ciphertext);
    decrypted = vigenere_decrypt(ciphertext, key);
    printf("%s\n", decrypted);
    */

    return 0;
}