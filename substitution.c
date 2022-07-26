#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Functions declerations
bool check_argc(int argc);
bool check_alpha(string s);
string convert_lowercase(string s);
bool check_repeat(string s);
int alpha_mapping(string s);
string substitute(string text, string key);

int main(int argc, string argv[])
{
    string userKey;
    int length;
    // Check if command-line arguments are only 1
    if (check_argc(argc) == false)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else
    {
        userKey = argv[1];
        length = strlen(userKey);
    }

    // Check if the key is 26 elements
    if (length != 26)
    {
        printf("Key must be 26 characters.\n");
        return 1;
    }

    // Check if the key is all alphabetical letters
    if (check_alpha(userKey) == false)
    {
        printf("Key must be alphabetical letters.\n");
        return 1;
    }

    // Convert lowercase
    convert_lowercase(userKey);

    // Check if the key has no repeated letters
    if (check_repeat(userKey) == true)
    {
        printf("Key must have no repeated letters.\n");
        return 1;
    }

    // Ask the user for a plaintext
    string plaintext = get_string("Plaintext:  ");

    // Mapping the key provided to substitution
    string ciphertext = substitute(plaintext, userKey);
    printf("ciphertext: %s\n", ciphertext);
    return 0;
}

// Check if command-line arguments are 2 including name of program
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

// Check if the key is all alpha letters
bool check_alpha(string s)
{
    int n = strlen(s);
    bool validAlpha = true;
    for (int i = 0; i < n && validAlpha; i++)
    {
        validAlpha = isalpha(s[i]);
    }
    return validAlpha;
}

string convert_lowercase(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        s[i] = tolower(s[i]);
    }
    return s;
}

// Check if there is any repeated letter in the key
bool check_repeat(string s)
{
    int n = strlen(s);
    bool check = true;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n && check == true; j++)
        {
            if (s[i] == s[j])
            {
                check = true;
            }
            else
            {
                check = false;
            }
        }
    }
    return check;
}

string substitute(string text, string key)
{
    int n = strlen(text);
    int finalMap[n];
    string smallMap = "abcdefghijklmnopqrstuvwxyz";
    string capitalMap = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (text[i] == smallMap[j] || text[i] == capitalMap[j])
            {
                finalMap[i] = j;
                break;
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                text[i] = toupper(key[finalMap[i]]);
            }
            else
            {
                text[i] = key[finalMap[i]];
            }
        }
    }
    return text;
}