#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]){

    printf("Caesar Cipher implementation by Prahlad\n");
    char* plaintext = malloc(100);

    printf("Enter the Plaintext: ");
    gets(plaintext);
    int L = strlen(plaintext);
    char *ciphertext = malloc(sizeof(char)*(L+1));
    int i, key;

    repeat:
    printf("Enter the key [1-25]: ");
    scanf("%d", &key);
    if(key>=1 && key<=25)
    {
        for(i=0;i<L;i++){
            if(isalpha(plaintext[i])) ciphertext[i] = (toupper(plaintext[i]) - 'A' + key)%26 + 'A';
            else ciphertext[i] = plaintext[i];
        }
        ciphertext[i] = 0;

        char *plaintext2 = malloc(sizeof(char)*(L+1));
        for(i=0;i<L;i++){
            if(isalpha(plaintext[i])) plaintext2[i] = (toupper(ciphertext[i]) - 'A' + 26 - key)%26 + 'A';
            else plaintext2[i] = ciphertext[i];
        }
        plaintext2[i] = 0;

        printf("Plain text: %s\n\nEncrypting.....\nCipher text: %s\n\nDecrypting....\nDecrypted Plain text: %s\n\n",plaintext, ciphertext,plaintext2);
    }
    else
    {
        printf("Please enter a valid key. \n");
        goto repeat;
    }

    //cryptanalysis

    printf("Performing cryptanalysis, brute force attack....\n");
    for(int k=1;k<=25;k++)
    {

        char *plaintext2 = malloc(sizeof(char)*(L+1));
        for(i=0;i<L;i++){
            if(isalpha(plaintext[i])) plaintext2[i] = (toupper(ciphertext[i]) - 'A' + 26 - k)%26 + 'A';
            else plaintext2[i] = ciphertext[i];
        }
        plaintext2[i] = 0;

        printf("Possible Plain text: %s\n", plaintext2);
    }
    return 0;
}

/*
Sample Inputs:

THE CASTLE WILL BE ATTACKED AT DAWN
3

THERE ARE FIVE DEFENSE CRUISERS IN DUNKIRK
11

ENEMY FORMED GROUPS OF FIFTEEN MEN HEADED TOWARDS US
25

*/
