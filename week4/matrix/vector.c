#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int LENGTH_VECTOR;
void initialize_vetors(int *vector_1, int *vector_2);
bool is_all_digits(char *s);
int* array_addition(int *vector_1, int *vetor_2);


int main(int argc, char *argv[])
{
    // Check for invalid command line arguments
    if (argc != 2)
    {
        printf("Usage: Vector length \n");
        return 1;
    }

    // Check if a string has non-digits
    if (!is_all_digits(argv[1]))
    {
        printf("Please anter valid number of vector length");
        return 1;
    }

    LENGTH_VECTOR = atoi(argv[1]);

    // Initialize two arrays
    int vector_1[LENGTH_VECTOR];
    int vector_2[LENGTH_VECTOR];

    initialize_vetors(vector_1, vector_2);


    // Add two arrays and print
    int *sum_arrays = array_addition(vector_1, vector_2);
    free(sum_arrays);

    return 0;
}

bool is_all_digits(char *s)
{
    int length = strlen(s);
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(s[i]))
        {
            return false;
        }
    }
    return true;
}

void initialize_vetors(int *vector_1, int *vector_2)
{
    for (int i = 0; i < LENGTH_VECTOR; i++)
    {
        printf("initialize vector 1: \n");
        scanf("%d", &vector_1[i]);
    }

    for (int i = 0; i < LENGTH_VECTOR; i++)
    {
        printf("initialize vector 2: \n");
        scanf("%d", &vector_2[i]);
    }

}

int* array_addition(int *vector_1, int *vector_2)
{
    int *sum_arrays= malloc(LENGTH_VECTOR * sizeof(int));;

    for (int i = 0; i < LENGTH_VECTOR; i++)
    {
        sum_arrays[i] = vector_1[i] + vector_2[i];
        printf("%i,", sum_arrays[i]);
    }
    printf("\n");
    return sum_arrays;
}