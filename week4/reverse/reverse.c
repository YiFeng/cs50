#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "wav.h"

typedef uint8_t BYTE;
int HEADER_SIZE = 44;

bool check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);
WAVHEADER read_header(FILE *input);
void reverse_wav(FILE *input, FILE *output);

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
    WAVHEADER header = read_header(FILE *input);

    // Use check_format to ensure WAV format
    if (!check_format(WAVHEADER header))
    {
        printf("Input is not a WAV file.\n");
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
    int block_size = get_block_size(WAVHEADER header);

    // Write reversed audio to file
    reverse_wav(input, output, block_size);

    fclose(input);
    fclose(output);

}

bool check_format(WAVHEADER header)
{
    // if the file is a wav file
    return (if(header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E'));
}

int get_block_size(WAVHEADER header)
{
    // number of channels multiplied by bytes per sample
    int block_size = header.numChannels * (header.bitsPerSample/8);
    return block_size;
}

WAVHEADER read_header(FILE *input)
{
    WAVHEADER header = malloc(sizeof(WAVHEADER));
    fread(header, sizeof(WAVHEADER), 1, input);
    return header;
}

void reverse_wav(FILE *input, FILE *output, int block_size)
{
    BYTE buffer[block_size];
    // move position dicator to the end of input file
    fseek(input, 0, SEEK_END);
    while ()
    {
        fseek(fp, -1, SEEK_CUR);
        fread(buffer, sizeof(buffer), 1, input)
    }

}