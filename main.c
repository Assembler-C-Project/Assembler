/*main.c
Written by: Nadeem Kabha and Elad Eytan Feldman
Date: 16/08/23
Prepose: This code reads assembly source files from command line arguments, processes them through preprocessing assembly and decoding phases, then generates output files with ".am" extension. */
#include "decoder.h"
#include "PreAssem.h"

int main(int argc, char *argv[])
{
    FILE *SourceFile;
    FILE *WorkFile;
    char *FileName;
    int i;
    
    /* Print a starting message */
    printf("Starting!\n");

    /* Iterate through command line arguments (file names) */
    for (i = 1; i < argc; i++)
    {
        /* Open the source file for reading */
        if ((SourceFile = fopen(*++argv, "r")) == NULL)
        {
            printf("Cannot open file %s\n", *argv);
            return 0;
        }

        /* Store the file name without extension */
        FileName = *argv;

        /* Extract file name without extension for output file */
        strtok(FileName, ".");

        /* Append ".am" to the file name for the working file */
        FileName = strcat(FileName, ".am");
        
        /* Open the working file for writing */
        if ((WorkFile = fopen(FileName, "w")) == NULL)
        {
            printf("Cannot open file %s\n", *argv);
            return 0;
        }

        /* Run the preprocessing assembly phase */
        RunPreAssem(SourceFile, WorkFile);

        /* Close the working file after writing */
        fclose(WorkFile);

        /* Reopen the working file for reading */
        if ((WorkFile = fopen(FileName, "r")) == NULL)
        {
            printf("Cannot open file %s\n", *argv);
            return 0;
        }

        /* Run the decoding phase */
        RunDecoder(WorkFile, FileName);
        
        /* Close the working file after reading */
        fclose(WorkFile);
    }
    
    return 0;
}
