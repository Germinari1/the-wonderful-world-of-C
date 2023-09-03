#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Check for command line args
    if (argc != 2)
    {
        printf("Usage: ./read infile\n");
        return 1;
    }

    // Create buffer to read into
    char buffer[7];

    // Create array to store plate numbers
    char *plates[8];

    FILE *infile = fopen(argv[1], "r");

    int idx = 0;
    while (fread(buffer, sizeof(char), 7, infile) == 7)
    {
        // Replace '\n' with '\0'
        buffer[6] = '\0';
        //allocate memory for 7 chars per plate
        plates[idx] = malloc(7*sizeof(char));
        // Save plate number in array
        strcpy(plates[idx], buffer);
        //go to next plate
        printf("%s\n", plates[idx]);
        free(plates[idx]);
        idx++;
    }
    //close file
    fclose(infile);
}
