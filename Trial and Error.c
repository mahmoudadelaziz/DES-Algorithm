#include <stdio.h>
#include <stdint.h>

int main()
{
    // Create an integer variable that will store the number we get from the user
    // int x;
    // int y;
    // printf("Enter two numbers");
    // scanf("%d", &x);
    // scanf("%d", &y);
    // printf("Multiplication result = %d", x * y);

    //  char str[] = "Hello";
    //  printf("%s \n", str);

    // Experimenting with uint types
    uint64_t array_of_bits = 0; //An array of 64 bits all set to zeros
    printf("The size of the uint64_t data type is %d bytes.\n", sizeof(array_of_bits));

    // Let's see if we can put a char in a uint64_t variable
    uint64_t c = 'A';
    printf("%d\n", c);
    printf("The size of one character in uint64_t = %d bytes.\n", sizeof(c));

    // Let's try 8 bits
    uint8_t d = 'A';
    printf("%d\n", d);
    printf("The size of one character in uint8_t = %d bytes.\n", sizeof(d));

    // Represent a string as an array of type uint_8_t
    uint8_t myParagraph[] = "Hi";
    printf("Text: %d\n", myParagraph[0]); //Prints the ASCII code for 'H' = 72
    printf("The size of myParagraph = %d bytes.\n", sizeof(myParagraph));

    // Try to put a character in a uint8_t
    char m = 'M';
    uint8_t my_m = m;
    printf("The character: %c\n", my_m); // This prints out the character
    printf("ASCII: %d\n", my_m); //This prints the ASCII code

    // Can we see the array itself?
    // for(int i = sizeof(my_m); i > 0; i--)
    // {
    //     printf("%d", m[i]);
    // }

    // Try to put a 4-char string in a uint64_t
    // char word[] = "Mill";
    // uint64_t myWord = word;
    // printf("The word: %s", myWord);
    // This didn't work

    
    
    
    return 0;

}
