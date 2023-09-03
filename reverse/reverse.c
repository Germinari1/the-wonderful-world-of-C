#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "wav.h"


int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if(argc != 3){
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }
    //Remember filenames
    char *infile = argv[1];
    char *outfile = argv[2];

    // Open input file for reading
    FILE *input  = fopen(infile, "r");
    if (input == NULL)
    {
        printf("the file cannot be opened\n");
        return 2;
    }
    // Read header
    WAVHEADER wh;
    fread(&wh,sizeof(WAVHEADER), 1, input);

    // Use check_format to ensure WAV format
    if (check_format(wh) == 1)
    {
        printf("The audio is not in the correct format.\n");
        return 3;
    }

    // Open output file for writing
    FILE *output = fopen(outfile, "w");
    if(output==NULL){
        printf("could not open output file.\n");
        return 4;
    }

    // Write header to file
    fwrite(&wh, sizeof(WAVHEADER), 1, output);

    // Use get_block_size to calculate [size of block = number of channels * bytes per sample]
    int bs = get_block_size(wh);

    // Write reversed audio to file
 if (fseek(input, bs, SEEK_END))
    {
        return 1;
    }

    BYTE buffer[bs];
    while (ftell(input) - bs > sizeof(wh))
    {
        // Cause fread() move the file pointer size forward
        // So, -2 * size
        if (fseek(input, -2 * bs, SEEK_CUR))
        {
            return 1;
        }
        fread(buffer, bs, 1, input);
        fwrite(buffer, bs, 1, output);
    }
    //close files
    fclose(input);
    fclose(output);
}

int check_format(WAVHEADER header) //true if WAVE marker is present in the file
{
    if (header.format[0] == 'W' && header.format[1] == 'A' && header.format[2] == 'V' && header.format[3] == 'E')
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int get_block_size(WAVHEADER header) //calculate [size of block = number of channels * bytes per sample]
{
    int block_size = header.numChannels * (header.bitsPerSample/8);
    return block_size;
}