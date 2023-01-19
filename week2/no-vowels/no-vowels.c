// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include <cs50.h>
#include <stdio.h>

string replace(string s);

int main(int argc, string argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("only enter one argument");
        return 1;
    }
    string converted_word = replace(argv[1]);
    printf("%s\n", converted_word);
}

string replace(string s)
{

}