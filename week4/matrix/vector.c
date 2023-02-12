#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int* vec;
    int len;
}
Vector;

Vector initialize_vetors(int len_vector);
bool is_number(char *s);
Vector vector_addition(Vector vector_1, Vector vector_2);
void print_vector(Vector vec_cur);

int main(int argc, char *argv[])
{
    // Check for invalid command line arguments
    if (argc != 2)
    {
        printf("Usage: Vector length \n");
        return 1;
    }

    // Convert argument into int
   int len_vector = atoi(argv[1]);
   if (len_vector == 0)
   {
        printf("Please enter valid number of vector length \n");
        return 1;
   }

    // Initialize two vectors
    Vector vector_1 = initialize_vetors(len_vector);
    Vector vector_2 = initialize_vetors(len_vector);

    // Add two vectors and print
    Vector sum_vectors = vector_addition(vector_1, vector_2);
    free(vector_1.vec);
    free(vector_2.vec);

    // Print sum of two vectors
    print_vector(sum_vectors);

    free(sum_vectors.vec);
    return 0;
}

bool is_number(char *s)
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

Vector initialize_vetors(int len_vector)
{
    Vector vec_cur;
    vec_cur.vec = calloc(len_vector, sizeof(int));
    vec_cur.len = len_vector;

    for (int i = 0; i < len_vector; i++)
    {
        printf("initialize vector element %i: \n", i+1);
        scanf("%d", &vec_cur.vec[i]);
    }
    return vec_cur;
}

Vector vector_addition(Vector vector_1, Vector vector_2)
{
    int len_vec = vector_1.len;
    Vector sum_vectors;
    sum_vectors.len = len_vec;
    sum_vectors.vec = calloc(len_vec, sizeof(int));

    for (int i = 0; i < len_vec; i++)
    {
        sum_vectors.vec[i] = vector_1.vec[i] + vector_2.vec[i];
    }
    return sum_vectors;
}

void print_vector(Vector vec_cur)
{
    for (int i = 0; i < vec_cur.len; i++)
    {
        printf("%d, ", vec_cur.vec[i]);
    }
    printf("\n");
}