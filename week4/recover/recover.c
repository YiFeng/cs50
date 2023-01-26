#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;
int BLOCK_SIZE = 512;


bool is_jpg_sig(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Check if the input file can be opened
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read blocks of input
    int i = 0;
    char file_name[8];
    FILE *output[50];
    BYTE buffer[BLOCK_SIZE];

    while (fread(buffer, sizeof(buffer), 1, input) == 1)
    {
        // Check first 4 bytes in each block
        if (is_jpg_sig(buffer))
        {
            if (i > 0)
            {
                fclose(output[i-1]);
            }
            sprintf(file_name, "%03d.jpg", i);
            output[i] = fopen(file_name, "w");
            fwrite(buffer, sizeof(buffer), 1, output[i]);
            i++;
        }
        else
        {
            output[i-1] = malloc(sizeof(buffer));
            fwrite(buffer, sizeof(buffer), 1, output[i-1]);
        }
    }
    fclose(input);
}

bool is_jpg_sig(BYTE buffer[])
{
    if ((buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff) && (buffer[3] >= 0xe0 && buffer[3] <= 0xef))
    {
        return true;
    }
    return false;
}