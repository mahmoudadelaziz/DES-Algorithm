#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Indices for Permutation Choice 1 for the Key
int PC1_Table[56] =
    {57, 49, 41, 33, 25, 17, 9,
     1, 58, 50, 42, 34, 26, 18,
     10, 2, 59, 51, 43, 35, 27,
     19, 11, 3, 60, 52, 44, 36,
     63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
     14, 6, 61, 53, 45, 37, 29,
     21, 13, 5, 28, 20, 12, 4};

// Indices for Permutation Choice 2 for the Key
int keyPermutationChoice_2_Table[48] =
    {14, 17, 11, 24, 1, 5,
     3, 28, 15, 6, 21, 10,
     23, 19, 12, 4, 26, 8,
     16, 7, 27, 20, 13, 2,
     41, 52, 31, 37, 47, 55,
     30, 40, 51, 45, 33, 48,
     44, 49, 39, 56, 34, 53,
     46, 42, 50, 36, 29, 32};

int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

bitset<28> Key_PC1_Left(bitset<64> fullKey)
{
    /*
    Takes the 64-bit key block,
    and returns the left side after performing Permutation Choice 1 (C0).
    */
    bitset<28> L0(0);
    for (int i = 1; i < 57; i++)
        L0[28 - i] = fullKey[64 - PC1_Table[i - 1]];
    return L0;
}

bitset<28> Key_PC1_Right(bitset<64> fullKey)
{
    /*
    Takes the 64-bit key block,
    and returns the right side after performing Permutation Choice 1 (D0).
    */
    bitset<28> R0(0);
    for (int i = 1; i < 57; i++)
        R0[28 - i] = fullKey[64 - PC1_Table[28 + i - 1]];
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
    bitset<28> roundShift_HalfKey(0);
    for (int i = number_of_shifts; i < 28 + number_of_shifts; i++)
        roundShift_HalfKey[i - number_of_shifts] = halfKey[((26 * number_of_shifts) + i) % 28];
    return roundShift_HalfKey;
}

bitset<48> generate_subKey(bitset<28> Ci, bitset<28> Di, int round_number)
{
    /*
    Takes the two 28-bit halves of the key after left-shifting (Ci, Di),
    and returns the 48-bit subKey of the current DES round.
    */

    // First, left shift
    bitset<28> C1 = circularLeftShift(Ci, shifts[round_number]);
    bitset<28> D1 = circularLeftShift(Di, shifts[round_number]);

    bitset<56> CDi(0);
    for (int i = 0; i < 28; i++)
    {
        CDi[i] = Di[i];
        CDi[28 + i] = Ci[i];
    }

    bitset<48> subKey_i(0);
    for (int i = 1; i < 48; i++)
        subKey_i[48 - i] = CDi[56 - keyPermutationChoice_2_Table[i - 1]];

    return subKey_i;
}

bitset<48> prep_keys(bitset<64> fullKey)
{
    //bitset<64> example_key("0001001100110100010101110111100110011011101111001101111111110001");
    // cout << "Key in bits: " << example_key << endl;
    bitset<28> C0 = Key_PC1_Left(fullKey);
    bitset<28> D0 = Key_PC1_Right(fullKey);

    bitset<28> C1 = circularLeftShift(C0, 1);
    bitset<28> D1 = circularLeftShift(D0, 1);


    bitset<48> K1 = generate_subKey(C1, D1);

}

int main()
{
    // Preparing keys (one time op)
    bitset<64> example_key("0001001100110100010101110111100110011011101111001101111111110001");
    bitset<28> C0 = Key_PC1_Left(example_key);
    bitset<28> D0 = Key_PC1_Right(example_key);
    // cout << "C0 (after PC1):   " << C0 << endl;
    // cout << "D0 (after PC1):   " << D0 << endl;

    bitset<28> C1 = circularLeftShift(C0, 1);
    bitset<28> D1 = circularLeftShift(D0, 1);
    // cout << "C1:   " << C1 << endl;
    // cout << "D1:   " << D1 << endl;

    bitset<48> K1 = generate_subKey(C1, D1);

    // cout << "K1: " << K1 << endl;
    // -------------------- Testing Key functions --------------------
    // Moving on...
}
