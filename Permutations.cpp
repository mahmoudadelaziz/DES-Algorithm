/* In this code file, I test the logic needed for DES permutations
using a simpler data block and a simpler permutation table for clarity. */
#include <iostream>

using namespace std;

int Perm_table[4] = {1, 3, 5, 7};

unsigned int permute(unsigned int word)
{
    unsigned int result = 0;

    for (int i = 0; i < 8; i++)
        result |= (((word & 1UL << (Perm_table[i] - 1)) != 0) << i);
    return result;
}

int main()
{
    unsigned int fullWord = 85;        //... 0101 0101
    cout << permute(fullWord) << endl; //... 0101 1111 (should output 15)

    return 0;
}