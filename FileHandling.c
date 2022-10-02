#include <stdio.h>

// I will use this step later to create functions for file handling

/*
REMEMBER: Our algorithm must operate on the bit level.

fgetc() is used to obtain input from a file single character at a time.
This function returns the ASCII code of the character read by the function.
*/

int main()
{
    // open the file
    char filename[256]; // Maximum number of bytes for a filename
    printf("Enter the name of the file you wish to process: \n");
    scanf("%s", filename);
    FILE *fp = fopen(filename, "r");

    // Return if could not open file
    if (fp == NULL)
    {
        printf("Could not open file!");
        return 0;
    }

    //Let the user name the output file
    char outputFileName[256]; // Maximum number of bytes for a filename
    printf("Enter the name of the output file: \n");
    scanf("%s", outputFileName);
    FILE *myOut = fopen(outputFileName, "w");

    do
    {
        // Taking input single character at a time
        char c = fgetc(fp);

        // Checking for end of file
        if (feof(fp))
            break;

        fprintf(myOut, "%d ", fgetc(fp)); //debugging step
    } while (1);

    // Close files
    fclose(myOut);
    fclose(fp);

    return (0);
}