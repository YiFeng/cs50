#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);
bool check_is_number(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    int target_digit = input[0] - '0';
    if (strlen(input) == 1)
    {
        return target_digit;
    }
    int target_decimal_num = strlen(input) - 1;
    int result = convert(input+1) + target_digit * (pow(10,target_decimal_num));
    return result;
}