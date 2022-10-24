#include <iostream>
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

int PC2_Table[48] =
    {14, 17, 11, 24, 1, 5,
     3, 28, 15, 6, 21, 10,
     23, 19, 12, 4, 26, 8,
     16, 7, 27, 20, 13, 2,
     41, 52, 31, 37, 47, 55,
     30, 40, 51, 45, 33, 48,
     44, 49, 39, 56, 34, 53,
     46, 42, 50, 36, 29, 32};

u64 Key_PC1(u64 fullKey)
{
    /* takes the full 64-bit key,
    and returns a 56-bit key by moving around the bits of the full key. */
    u64 newKey = 0;
    for (int i = 0; i < 56; i++)
        newKey |= (fullKey >> (64 - PC1_Table[56 - 1 - i]) & 1) << i;
    return newKey;
}

u64 Key_PC2(u64 CnDn)
{
    /* takes the CnDn (after bit-rotation),
    and returns a 48-bit subkey for the current DES round. */
    u64 newKey = 0;
    for (int i = 0; i < 48; i++)
        newKey |= (CnDn >> (56 - PC2_Table[48 - 1 - i]) & 1) << i;
    return newKey;
}

int main()
{
    u64 example_key = 0x133457799BBCDFF1;
    // this loop prints out the result in binary
    cout << "Full key:\n";
    for (int i = 0; i < 64; i++)
        cout << ((example_key & 1UL << (63 - i)) != 0);

    cout << endl;
    u64 result = Key_PC1(example_key);
    cout << "Key PC1 result:\n";
    for (int i = 0; i < 64; i++)
        cout << ((result & 1UL << (63 - i)) != 0);

    cout << endl;
    cout << "Key PC1 result should be: \n0000000011110000110011001010101011110101010101100110011110001111" << endl;

    // Get C0 and D0
    unsigned int C0 = 0;
    unsigned int D0 = 0;

    C0 = int((result & 0x00FFFFFFF0000000LL) >> 28);
    D0 = int((result & 0x000000000FFFFFFFLL));

    // Checking...
    cout << "C0: \n";
    for (int i = 0; i < 28; i++)
        cout << ((C0 & 1UL << (27 - i)) != 0);

    cout << "\nD0: \n";
    for (int i = 0; i < 28; i++)
        cout << ((D0 & 1UL << (27 - i)) != 0);

    // Round Left-shifting
    unsigned int C1 = 0;
    unsigned int D1 = 0;

    // Left-shift by one
    C1 = (((C0 << 1) | (C0 >> (28 - 1))) & 0x000000000FFFFFFFLL);
    D1 = (((D0 << 1) | (D0 >> (28 - 1))) & 0x000000000FFFFFFFLL);

    // Merging C1-D1
    u64 subkey_before_PC2 = ((u64)C1) << 28 | D1;

    cout << "\nC1D1:\n";
    for (int i = 0; i < 64; i++)
        cout << ((subkey_before_PC2 & 1UL << (63 - i)) != 0);

    u64 K1 = Key_PC2(subkey_before_PC2);

    cout << "\nK1:\n";
    for (int i = 0; i < 64; i++)
        cout << ((K1 & 1UL << (63 - i)) != 0);



    return 0;
}