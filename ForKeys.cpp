#include <iostream>
#include <bitset> //Just for checking

using namespace std;

typedef unsigned long long u64;

int PC1_Table[56] =
    {57, 49, 41, 33, 25, 17, 9,
     1, 58, 50, 42, 34, 26, 18,
     10, 2, 59, 51, 43, 35, 27,
     19, 11, 3, 60, 52, 44, 36,
     63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
     14, 6, 61, 53, 45, 37, 29,
     21, 13, 5, 28, 20, 12, 4}; // list of indices

u64 Key_PC1(u64 fullKey)
{
    /* takes the full 64-bit key,
    and returns a 56-bit key by moving around the bits of the full key. */
    u64 newKey = 0;
    bool mask = 0;
    int index_to_set = 0;
    for (int i = 0; i < 56; i++)
    {
        mask = ((fullKey & 1UL << (64 - PC1_Table[i])) != 0);
        index_to_set = 63 - i;
        newKey |= mask << index_to_set;

        // newKey |= (fullKey >> (((64 - PC1_Table[i]) & 1)) != 0) << (63-i);
        // newKey |= (fullKey >> (63 - PC1_Table[64 - i]) & 1) << i;
    }
    // newKey = newKey | (((fullKey & (1UL << (64-PC1_Table[i])))) != 0) << (55-i);
    return newKey;
}

int main()
{

    u64 example_key = 0x133457799BBCDFF1;

    // Debugging (this loop prints out the result in binary)
    for (int i = 0; i < 64; i++)
        cout << ((Key_PC1(example_key) & 1UL << (63 - i)) != 0);
    cout << endl;
    // cout << "\nShould be: \n";
    // cout << "0001001100110100010101110111100110011011101111001101111111110001";

    // cout << "my key     : " << bitset<64>(Key_PC1(example_key)) << endl;

    cout << "should be: \n0000000011110000110011001010101011110101010101100110011110001111" << endl;
    // This is the correct result from a solved example
    return 0;
}