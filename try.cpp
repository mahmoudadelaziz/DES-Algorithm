/*
    This file is just for trial and error.
    Feel free to experiment here.
*/

#include <iostream>
#include <bits/stdc++.h>

int round_no;

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

bitset<28> Key_PC1_Left(bitset<64> fullKey)
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

bitset<28> Key_PC1_Right(bitset<64> fullKey)
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

// Circular left shift
bitset<28> circularLeftShift(bitset<28> halfKey, int number_of_shifts)
{
    /*
    Takes a half of the key after PC1 (C0, or D0),
    and a number of shifts (either 1 or 2) that depends on which round we're in,
    and performs left-shift on it (as required by the DES round)
    */
    bitset<28> roundShiftedHalfKey(0);
    for (int i = number_of_shifts; i < 28 + number_of_shifts; i++)
        roundShiftedHalfKey[i - number_of_shifts] = halfKey[((26 * number_of_shifts) + i) % 28];
    return roundShiftedHalfKey;
}

int main()
{
    bitset<64> fullKey(0x133457799BBCDFF1);
    cout << "C0:                              " << Key_PC1_Left(fullKey) << endl;
    // cout << "D0:    " << Key_PC1_Right(fullKey) << endl;

    // cout << "left shift C0 by one:      " << (Key_PC1_Left(fullKey) << 1) << endl;
    cout << "(Circular) left shift C0 by one: " << circularLeftShift(Key_PC1_Left(fullKey), 1) << endl;
    cout << "It should be:                    "
         << "1110000110011001010101011111" << endl;
    cout << "(Circular) left shift C0 by two: " << circularLeftShift(Key_PC1_Left(fullKey), 2) << endl;
    cout << "(Circular) left shift D0 by one: " << circularLeftShift(Key_PC1_Right(fullKey), 1) << endl;
    cout << "It should be:                    "
         << "1010101011001100111100011110" << endl;
    // playing with circular loops
    // cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;
    // cout << "Playing with circular arrays... Exploring!" << endl;
    // cout << "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" << endl;

    // round_no = 3;
    // int arr [] = {3, 6, 8, 9, 11};
    // for (int i = round_no; i < 5 + round_no; i++)
    // {
    //     cout << arr[i % 5] << " ";
    // }
    // cout << "\nDone!" << endl;

    return 0;
}