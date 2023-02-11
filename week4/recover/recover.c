#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

int BLOCK_SIZE = 512;


bool is_jpg_sig(uint8_t buffer[]);

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

    // Count how many jpg files it has

    // Read blocks of input
    int jpg_name_num = 0;
    char file_name[8];
    FILE *output = NULL;
    uint8_t buffer[BLOCK_SIZE];

    while (fread(buffer, sizeof(buffer), 1, input) > 0)
    {
        // Check first 4 bytes in each block
        if (is_jpg_sig(buffer))
        {
            if (output != NULL)
            {
                fclose(output);
            }
            output = NULL;
            // if the first 4 bytes indicates its a jpg, then create a new file
            sprintf(file_name, "%03d.jpg", jpg_name_num);
            output = fopen(file_name, "w");
            jpg_name_num++;
        }
        // make sure the output file is valid
        if (output != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, output);
        }
    }
    fclose(input);
    fclose(output);
}

bool is_jpg_sig(uint8_t buffer[])
{
    return (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
    && (buffer[3] >= 0xe0 && buffer[3] <= 0xef);
}
