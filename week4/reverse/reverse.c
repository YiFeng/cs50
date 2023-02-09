#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wav.h"

typedef uint8_t BYTE;
int HEADER_SIZE = sizeof(WAVHEADER);

bool check_format(WAVHEADER *header);
int get_block_size(WAVHEADER *header);
void reverse_wav(FILE *input, FILE *output, int block_size);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav");
        return 1;
    }

    // Open input file for reading
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Read header into an array
    // Create an array to save header info
    WAVHEADER *header = malloc(sizeof(WAVHEADER));
    fread(header, sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    if (!check_format(header))
    {
        printf("Input is not a WAV file.\n");
        return 1;
    }

    // Open output file for writing
    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Write header to file
    fwrite(header, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate size of block
    int block_size = get_block_size(header);

    // Write reversed audio to file
    reverse_wav(input, output, block_size);
    free(header);
    fclose(input);
    fclose(output);

}

bool check_format(WAVHEADER *header)
{
    // if the file is a wav file
    return (header->format[0] == 'W' && header->format[1] == 'A' && header->format[2] == 'V' && header->format[3] == 'E');
}

int get_block_size(WAVHEADER *header)
{
    // number of channels multiplied by bytes per sample
    int block_size = header->numChannels * (header->bitsPerSample/8);
    return block_size;
}

void reverse_wav(FILE *input, FILE *output, int block_size)
{
    BYTE buffer[block_size];
    // move position dicator to the end of input file
    fseek(input, 0, SEEK_END);
    while (ftell(input) > HEADER_SIZE)
    {
        fseek(input, -1 * block_size, SEEK_CUR);
        fread(buffer, sizeof(buffer), 1, input);
        fwrite(buffer, sizeof(buffer), 1, output);
        fseek(input, -1 * block_size, SEEK_CUR);
    }

}