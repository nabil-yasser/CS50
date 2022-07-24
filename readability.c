#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_char(string input);
int count_words(string input);
int count_sentences(string input);

int main(void)
{
    // Get user's string
    string userInput = get_string("Text: ");

    // Count characters
    int letters = count_char(userInput);

    // Count Words
    int words = count_words(userInput);

    // Count Sentences
    int sents = count_sentences(userInput);

    float L = (letters * 100.0) / words;
    float S = (sents * 100.0) / words;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    printf("Letters: %i\n", letters);
    printf("Words: %i\n", words);
    printf("Sentences: %i\n", sents);
    printf("L: %f\n", L);
    printf("S: %f\n", S);
    printf("Index: %i\n", index);

    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_char(string input)
{
    int i = 0, lCount = 0;
    while (input[i] != '\0')
    {
        if ((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z'))
        {
            lCount++;
        }
        i++;
    }
    return lCount;
}

int count_words(string input)
{
    int i = 0, wCount = 0;
    while (input[i] != '\0')
    {
        if (input[i] == ' ')
        {
            wCount++;
        }
        i++;
    }
    return wCount + 1;
}

int count_sentences(string input)
{
    int i = 0, sCount = 0;
    while (input[i] != '\0')
    {
        if (input[i] == '.' || input[i] == '?' || input[i] == '!')
        {
            sCount++;
        }
        i++;
    }
    return sCount;
}