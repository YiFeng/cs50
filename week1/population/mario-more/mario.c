#include <cs50.h>
#include <stdio.h>

int get_height(void);
void print_pyramids(int n);

int main(void)
{
    int height = get_height();
    print_pyramids(height);

}

// Get a number between 1 to 8 as the height
int get_height(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);
    return height;
}

// Print spaces
void print_space(int num_space)
{
    // print space
    int j = 0;
    while (j < num_space)
    {
        printf(" ");
        j++;
    }
}
// Print hash
void print_hash(int num_hash)
{
    int z = 0;
    while (z < num_hash)
    {
        printf("#");
        z++;
    }
}

// Print each row
void print_row(int n, int i)
{
    int num_space = n - (i + 1);
    int num_hash = i + 1;
    // print space
    print_space(num_space);
    // print hash
    print_hash(num_hash);
    // print two spaces
    printf("  ");
    // print hash
    print_hash(num_hash);
    printf("\n");
}

// Print pyramids
void print_pyramids(int n)
{
    for (int i = 0; i < n; i++)
    {
        print_row(n, i);
    }
}