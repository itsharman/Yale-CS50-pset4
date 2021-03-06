/**
 * Harmanpreet Singh
 * recover.c
 *
 * CPSC 100
 * Problem Set 4
 *
 * Recovers JPEGs from a corrupted SD card.
 */
 
#include <stdint.h>
#include <stdio.h>

#define BLOCK_SIZE 512
//create a block of 512 bytes
typedef uint8_t BYTE;
BYTE block[BLOCK_SIZE];
//create a name checker
char name[8];

int main(int argc, char* argv[])
{
    //open the card file
    FILE* inputFile = fopen("card.raw", "r");
    
    //check if you are able to open the card file
    if (inputFile == NULL) {
        fclose(inputFile);
        printf("Error: could not open file card.raw...");
        return 1;
    }

    //initialize jpg counter to 0
    int counter = 0;
    //declare and initialize output file
    FILE* outputFile = NULL;
  
    //iterate through file
    while (!feof(inputFile))
    // while (fread(block, BLOCK_SIZE, 1, inputFil))
    {
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && 
        (block[3] == 0xe0 || block[3] == 0xe1)) {
            //if outputFile is open, close it
            if (outputFile != NULL) fclose(outputFile);
            //else {
            //give name to jpg
            sprintf(name, "%03i.jpg", counter);
            //open jpg
            outputFile = fopen(name, "w");
            //increment counter
            counter++;
            //write to outputFile
            fwrite(block, BLOCK_SIZE, 1, outputFile);
            // }
        }
        else if (counter > 0) fwrite(block, BLOCK_SIZE, 1, outputFile);
        //read next 512 bytes (next block)
        fread(block, BLOCK_SIZE, 1, inputFile);
    }
    // close outfile
    fclose(outputFile);
    // close infile
    fclose(inputFile);
    // that's all folks
    return 0;
}

//???? 
//PROFIT.