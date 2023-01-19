#include <cs50.h>
#include <stdio.h>

typedef struct
{
    int credit_sum;
    int initial_2_num[2];
    int length;
}
credits;

credits calculate_credit_card(long number);
void check_card(credits credict_info);

int main(void)
{
    // Get credit card number
    long credit_num = get_long("Number: ");

    // Calculate defined sum of credit card number
    credits credict_info  = calculate_credit_card(credit_num);

    // Check if it is valid, if yes, which bank
    check_card(credict_info);
}


credits calculate_credit_card(long number)
{
    // Get initial values
    int i = 1;
    int odd_sum = 0;
    int even_sum = 0;
    long quotient = number;
    int remainder = 0;
    int initial_2_num[2];

    do
    {
        // Get the quotient
        quotient = number / 10;
        // get the remainder
        remainder = number % 10;

        if (i % 2 == 0)
        {
            int product = remainder * 2;
            if (product >= 10)
            {
                product = product / 10 + product % 10;
            }
            even_sum += product;
        }
        else
        {
            odd_sum += remainder;
        }

        if (number < 100 && number > 9)
        {
            initial_2_num[0] = quotient;
            initial_2_num[1] = remainder;
        }

        i++;
        number = quotient;

    }
    while (quotient > 0);
    int sum = even_sum + odd_sum;
    credits credict_info;
    credict_info.credit_sum = sum;
    credict_info.initial_2_num[0] = initial_2_num[0];
    credict_info.initial_2_num[1] = initial_2_num[1];
    credict_info.length = i - 1;

    return credict_info;
}

void check_card(credits credict_info)
{
    string check_result = "INVALID";

    if (credict_info.credit_sum % 10 != 0)
    {
        printf("INVALID\n");
        return;
    }
    else
    {

        if (credict_info.initial_2_num[0] == 4 && (credict_info.length == 13 || credict_info.length ==16))
        {
            check_result = "VISA";
        }
        if (credict_info.initial_2_num[0] == 3 && credict_info.length == 15)
        {
            if (credict_info.initial_2_num[1] == 4 || credict_info.initial_2_num[1] == 7)
            {
                check_result = "AMEX";
            }
        }

        if (credict_info.initial_2_num[0] == 5 && credict_info.initial_2_num[1] <6 && credict_info.initial_2_num[1] > 0 && credict_info.length == 16)
        {
            check_result = "MASTERCARD";
        }

    }
    printf("%s\n", check_result);
}