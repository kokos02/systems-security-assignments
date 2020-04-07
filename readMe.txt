Nikolaos Kokolantonakis
3727

In general: For every function we get the plain text from the TextInput macro. So if we want
to change the plaintext we change that. SIZE_OF_TEXT is the length of TextInput.


One time pad:

We generate the random key with from the dev/urandom through the getRandomkey function
and then we pass the string as argument to the functions. We need to print the cipher
in hex format in order not to lose any characters in case we have
any non printable charactes which may cause problems like
the backslash character. In this algorithm we xor each character of the 
plain text with the corresponding character from 
the key. To decrypt we xor each character of the ciphertext with the corresponding
from the key.

Caesar encrypt: 

For this method we move each character from the plain text N steps further on the ascii table. if we reach the end z or Z
or 9 we go to the begining again a or A or 0. To decrypt we go 4 steps back and if we reach a or A or 9 we go to z or Z 
or 0.

Spartan encrypt: 

The len argument specifies the length of the plain text. In this method to encrypt we take one letter from the plain text
and then we move circle times to get the next character, if we reach the end of the plain text we go to the begining
again and that's how we make te ciphertext or if we already used the character we point to we move to the next 
character. To decrypt we move on the ciphertext step(ciphertext/circ) times to get the next character same procedure
applies if we reach the end or point to an already used character as above.



Vigenere_encrypt: 

Here we first make the table with the alphabet. To encrypt we match the corresponding column of the 
index of each character of the plain text in the array to the index of the corresponding character on the key again 
in the array to make the cipher text. To decrypt we use each character of the key index as row of the array and we 
use the corresponding character of the ciphertext as index to that row and we take the correspong letter from the
alphabet as the number on wich we found the letter of the cipher text.
