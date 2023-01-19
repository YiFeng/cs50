#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool is_valid_key(string s);
void convert_cipher(string s, string key);
void convert_diff_key(char key[]);
bool is_letter(char l);
bool has_duplicate(string s);

int main(int argc, string argv[])
{
    // if no or more than 2 arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // printf("%s\n", has_duplicate(argv[1]) ? "true" : "false");
    // if invalid arguments
    bool is_valid = is_valid_key(argv[1]);
    if (!is_valid)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // get string as plaintext
    string plaintext = get_string("plaintext: ");

    // convert plain text to cipher text
    convert_cipher(plaintext, argv[1]);

    return 0;

}

bool is_letter(char l)
{
    l =  tolower(l);
    return l >= 'a' && l <= 'z';
}

bool has_duplicate(string s)
{
    int n = strlen(s);
    for (int i = 0; i < n; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (tolower(s[i]) == tolower(s[j]))
            {
                return true;
            }
        }
    }
    return false;
}

bool is_valid_key(string s)
{
    // length of input
    if (strlen(s) != 26)
    {
        return false;
    }
    // if it is a letter
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!is_letter(s[i]))
        {
            return false;
        }
    }
    // if it has duplicate
    return !has_duplicate(s);
}

void convert_cipher(string s, string key)
{
    convert_diff_key(key);
    int len = strlen(s);
    char cipher_letter = 0;
    printf("ciphertext: ");

    for (int i = 0; i < len; i++)
    {
        // if not a char keep original
        cipher_letter = s[i];

        // if it is a char
        int position = tolower(s[i]) - 'a';
        if (position >= 0 &&  position < 26)
        {
            cipher_letter = s[i] + key[position];
        }
        printf("%c", cipher_letter);
    }
    printf("\n");
}

void convert_diff_key(string key) {
  int len = strlen(key);
  for (int i = 0; i < len; i++) {
    key[i] = tolower(key[i]) - (i + 'a');
  }
}


// better design?
bool has_duplicate(int i, string s)
{
    int n = strlen(s);
    if (i < 1)
    {
        return false;
    }
    s[n-1] = '\0';
    bool result = has_duplicate(i-1, s);

    for (int)




}
