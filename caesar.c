#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

bool check_argc(int argc);
bool check_digits(string input);
int convert_key(string input);
string encrypt(string s, int key);

int main(int argc, string argv[])
{
    // Check if terminal argument is a single one
    if (check_argc(argc) == true)
    {
        ;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Check if argv is all digits
    string userInput = argv[1];
    bool chkDigit = check_digits(userInput);
    int key;
    if (chkDigit == true)
    {
        key = convert_key(userInput);
    }
    else
    {
        key = 0;
        printf("Usage: ./caesar key\n");
        return 1;
    }
    if (key > 0)
    {
        string plaintext = get_string("Plaintext:  ");
        string ciphertext = encrypt(plaintext, key);
        printf("Ciphertext: %s\n", ciphertext);
    }
    else
    {
        printf("Usage: ./caesar key\n");
    }
}

bool check_argc(int argc)
{
    if (argc == 2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool check_digits(string input)
{
    int i = 1;
    bool chkDigit = isdigit(input[i - 1]);
    while (input[i] != '\0' && chkDigit == true)
    {
        i++;
        chkDigit = isdigit(input[i - 1]);
    }
    return chkDigit;
}

int convert_key(string input)
{
    int key = atoi(input);
    return key;
}

string encrypt(string s, int key)
{
    int i = 0;
    key %= 26;
    int modChar;
    while (s[i] != '\0')
    {
        if (isalpha(s[i]))
        {
            modChar = s[i] + key;
            if ((isupper(s[i]) && modChar > 'Z') || (islower(s[i]) && modChar > 'z'))
            {
                s[i] = modChar - 26;
            }
            else
            {
                s[i] = modChar;
            }
        }
        i++;
    }
    return s;
}