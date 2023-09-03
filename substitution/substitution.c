#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 26

bool check_uniqueness(char *key);

int main(int argc, string argv[])
{
    //validate command line args
    if(argc!=2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if(strlen(argv[1])!=SIZE){
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for(int i=0; i<SIZE; i++){
        if (!isalpha(argv[1][i])){
            printf("Key must contain 26 alphabetical characters.\n");
            return 1;
        }
    }
    if(!check_uniqueness(argv[1]))
    {
        printf("The key must contain 26 UNIQUE characters");
        return 1;
    }


    //get plaintext from user
    char *plaintxt;
    plaintxt = get_string("Plaintext: ");

    //store key in variable and turn chars into uppercase
    string key = argv[1];
    for(int i=0;i<strlen(key);i++)
    {
        key[i] = toupper(key[i]);
    }

    //convert plaintext into cyphertext
    string ciphertext = plaintxt;

    for (int i = 0; i < strlen(ciphertext); i++)
    {
        //If block to ignore punctuation.

        //Checks if the plaitext is a capital letter, if so it takes off 97 to get the index to 0 and assigns the corresponding key value to the ciphertext.
        if (isupper(plaintxt[i]))
        {
            ciphertext[i] = key[plaintxt[i] - 65];
        }
        //Same as previous step but for lowercase letters. Takes off 97 this time and then converts the assigned character to lowercase as the key is all uppercase characters.
        if (islower(plaintxt[i]))
        {
            ciphertext[i] = key[plaintxt[i] - 97];
            ciphertext[i] = tolower(ciphertext[i]);
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}
    bool check_uniqueness(char *key)
    {
        int counter = 0;
        //loop through alphabet letters and check with key
        for(char char_current = 'A'; char_current<='Z'; char_current++)
        {
            for(int i=0; i<=strlen(key); i++)
            {
                if(char_current == key[i])
                {
                    counter++;
                    break; //ensure that loop stops when letter in found (garantee that every letter is counted only once)
                }
            }
        }
    return (counter == 26);
    }