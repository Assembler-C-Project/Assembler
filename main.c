#include "decoder.h"
#include "PreAssem.h"

int main(int argc, char *argv[]) 
{
    FILE *SourceFile;
    FILE *WorkFile;
    char *FileName;
    int i;

    for (i = 1; i < argc; i++)
    {
        if((SourceFile = fopen(*++argv, "r")) == NULL)
        {
        printf("Cannot open file %s\n",*argv);
        return 0;
        }

        FileName = *argv;

        strtok(FileName, ".");

        FileName = strcat(FileName, ".am");
        if((WorkFile = fopen(FileName, "w")) == NULL)
        {
        printf("Cannot open file %s\n",*argv);
        return 0;
        }

        RunPreAssem(SourceFile, WorkFile); 

        if((WorkFile = fopen(FileName, "r")) == NULL)
        {
        printf("Cannot open file %s\n",*argv);
        return 0;
        }
        
        RunDecoder(WorkFile, FileName);
    }
    writeToEntFile("TestENT", "this is a test 123");
    writeToExtFile("TestEXT", "this is a test 123");
    return 0;
}
