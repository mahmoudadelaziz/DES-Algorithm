/*
    This file is just for trial and error.
    Feel free to experiment here.
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define BIT_ARRAY_LENGTH 64

int keyPermutationChoice_1_Table[56] =
    {57, 49, 41, 33, 25, 17, 9,
     1, 58, 50, 42, 34, 26, 18,
     10, 2, 59, 51, 43, 35, 27,
     19, 11, 3, 60, 52, 44, 36,
     63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
     14, 6, 61, 53, 45, 37, 29,
     21, 13, 5, 28, 20, 12, 4};

bitset<28> C0(bitset<64> fullKey)
{
    /*
    Takes the 64-bit data block,
    and returns the left side after performing Initial Permutation.
    */
    bitset<28> L0(0);
    for (int i = 1; i < 57; i++)
        L0[28 - i] = fullKey[64 - keyPermutationChoice_1_Table[i - 1]];
    return L0;
}

bitset<28> D0(bitset<64> fullKey)
{
    /*
    Takes the 64-bit data block,
    and returns the right side after performing Initial Permutation.
    */
    bitset<28> R0(0);
    for (int i = 1; i < 57; i++)
        R0[28 - i] = fullKey[64 - keyPermutationChoice_1_Table[28 + i - 1]];
    return R0;
}

int main()
{
    bitset <64> fullKey (0x133457799BBCDFF1);
    cout << "C0:    " << C0(fullKey) << endl;
    cout << "D0:    " << D0(fullKey) << endl;
    return 0;
}