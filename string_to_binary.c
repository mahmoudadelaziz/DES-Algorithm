#include <stdio.h>
#include <string.h>

int main()
{
    int i;

    char *string = "Now let's try this train of bytes"; // ASCII Code: 97

    for (i = 0; i < 8 * strlen(string); i++)
        printf("%d", 0 != (string[i / 8] & 1 << (~i & 7)));

    printf("\n");
}