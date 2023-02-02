#include <stdio.h>

int main(int argc, char *argv[])
{
    // Check for invalid command line arguments
    if (argc != 2)
    {
        printf("Usage: Vector length \n");
        return 1;
    }

    if (!isdigit(argv[1]))
    {
        printf("Please anter valid number of vector length");
        return 1;
    }

    // Get user input

}