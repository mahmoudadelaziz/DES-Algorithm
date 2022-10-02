// I will use this step later to create functions for file handling
#include <stdio.h>

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

    FILE *myOut = fopen("Answer.txt", "w");
    do
    {
        // Taking input single character at a time
        char c = fgetc(fp);

        // Checking for end of file
        if (feof(fp))
            break;

        fprintf(myOut, "%d ", fgetc(fp));
    } while (1);

    // Close files
    fclose(myOut);
    fclose(fp);

    return (0);
}