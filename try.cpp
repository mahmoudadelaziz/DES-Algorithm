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

int keyPermutationChoice_2_Table[48] =
    {14, 17, 11, 24, 1, 5,
     3, 28, 15, 6, 21, 10,
     23, 19, 12, 4, 26, 8,
     16, 7, 27, 20, 13, 2,
     41, 52, 31, 37, 47, 55,
     30, 40, 51, 45, 33, 48,
     44, 49, 39, 56, 34, 53,
     46, 42, 50, 36, 29, 32};

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

// Generate subkey Ki
bitset<48> subKey(bitset<28> Ci, bitset<28> Di)
{
    /*
    Takes the two 28-bit halves of the key after left-shifting (Ci, Di),
    and returns the 48-bit subKey of the current DES round.
    */

    // First, combine C1 and D1
    bitset<56> CDi(0);
    for (int i = 0; i < 28; i++)
    {
        CDi[i] = Di[i];
        CDi[28 + i] = Ci[i];
    }

    bitset<48> subKey_i(0);
    for(int i = 1; i < 48; i++)
    {
        subKey_i[48 - i] = CDi[56 - keyPermutationChoice_2_Table[i-1]];
    }

    // for (int i = 1; i < 28; i++)
    // {
    //     // Right part of Ki
    //     subKey_i[i - 1] = Di[27 - keyPermutationChoice_2_Table[i - 1]];
    //     // Left part of Ki (prints all zeros?! Why?!)
    //     // subKey_i[28 + i - 1] = Ci[28 - keyPermutationChoice_2_Table[28 + i - 1]];
    // }
    return subKey_i;
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

    // Generate subkey K1


    bitset<56> CDi(0);
    for (int i = 0; i < 28; i++)
    {
        CDi[i] = circularLeftShift(Key_PC1_Left(fullKey), 1)[i];
        CDi[28 + i] = circularLeftShift(Key_PC1_Right(fullKey), 1)[i];
    }
    cout << "D1 and C1 combined: " << CDi << endl;
    
    cout << "K1:           " << subKey(circularLeftShift(Key_PC1_Left(fullKey), 1), circularLeftShift(Key_PC1_Right(fullKey), 1)) << endl;
    cout << "K1 Should be: " << "000110110000001011101111111111000111000001110010" << endl;
    
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