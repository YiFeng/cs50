#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int start_size;
    do
    {
        start_size = get_int("Please enter a number as starting population size: ");
    }
    while (start_size < 9);

    // TODO: Prompt for end size
    int end_size;
    do
    {
        end_size = get_int("Please enter a number as end population size: ");
    }
    while (end_size < start_size);

    // TODO: Calculate number of years until we reach threshold
    int num_year = 0;
    while (start_size < end_size)
    {
        int born_size = start_size / 3;
        int die_size = start_size / 4;
        start_size = start_size + born_size - die_size;
        num_year++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", num_year);
}
