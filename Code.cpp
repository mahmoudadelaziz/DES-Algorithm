/*
    -- WORK IN PROGRESS! --
    This is the main code file.
    All functions implemented in other code files
    must be integrated into this file in the end
    before we deliver the final executable.

    >> Walking through the example at:
    https://captanu.wordpress.com/2015/04/05/des/
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// Indices for the Initial Permuation
int IP_Table[64] =
    {
        58,
        50,
        42,
        34,
        26,
        18,
        10,
        2,
        60,
        52,
        44,
        36,
        28,
        20,
        12,
        4,
        62,
        54,
        46,
        38,
        30,
        22,
        14,
        6,
        64,
        56,
        48,
        40,
        32,
        24,
        16,
        8,
        57,
        49,
        41,
        33,
        25,
        17,
        9,
        1,
        59,
        51,
        43,
        35,
        27,
        19,
        11,
        3,
        61,
        53,
        45,
        37,
        29,
        21,
        13,
        5,
        63,
        55,
        47,
        39,
        31,
        23,
        15,
        7,
};

// Indices for Permutation Choice 1 for the Key
int keyPermutationChoice_1_Table[56] =
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

int EP_Table[48] =
    {32, 1, 2, 3, 4, 5, 4, 5,
     6, 7, 8, 9, 8, 9, 10, 11,
     12, 13, 12, 13, 14, 15, 16, 17,
     16, 17, 18, 19, 20, 21, 20, 21,
     22, 23, 24, 25, 24, 25, 26, 27,
     28, 29, 28, 29, 30, 31, 32, 1};

bitset<64> data_to_blocks(string ourPlainText)
{
    /*
    This function takes the input plaintext,
    and returns a 64-bit data block.
    */
    string binaryString;
    for (int i = 0; i < 8; i++)
    {
        bitset<8> ch(ourPlainText[i]);
        binaryString += ch.to_string();
    }

    bitset<64> dataBlock(binaryString);
    return dataBlock;
}

bitset<32> L0(bitset<64> Data_after_IP)
{
    /*
    Takes the 64-bit data block,
    and returns the left side after performing Initial Permutation.
    */
    bitset<32> L0(0);
    for (int i = 1; i < 65; i++)
        L0[32 - i] = Data_after_IP[32 - IP_Table[i - 1]];
    return L0;
}

bitset<32> R0(bitset<64> Data_after_IP)
{
    /*
    Takes the 64-bit data block,
    and returns the right side after performing Initial Permutation.
    */
    bitset<32> R0(0);
    for (int i = 1; i < 65; i++)
        R0[32 - i] = Data_after_IP[64 - IP_Table[32 + i - 1]];
    return R0;
}

bitset<28> Key_PC1_Left(bitset<64> fullKey)
{
    /*
    Takes the 64-bit key block,
    and returns the left side after performing Permutation Choice 1 (C0).
    */
    bitset<28> L0(0);
    for (int i = 1; i < 57; i++)
        L0[28 - i] = fullKey[64 - keyPermutationChoice_1_Table[i - 1]];
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
    bitset<28> roundShift_HalfKey(0);
    for (int i = number_of_shifts; i < 28 + number_of_shifts; i++)
        roundShift_HalfKey[i - number_of_shifts] = halfKey[((26 * number_of_shifts) + i) % 28];
    return roundShift_HalfKey;
}

bitset<48> generate_subKey(bitset<28> Ci, bitset<28> Di)
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
    for (int i = 1; i < 48; i++)
        subKey_i[48 - i] = CDi[56 - keyPermutationChoice_2_Table[i - 1]];

    return subKey_i;
}

bitset<48> expansionPermutation(bitset<32> R0)
{
    /*
    Takes the right half of data after IP (R0),
    and returns a 48-bit representation of it after Expansion Permutation.
    */
    bitset<48> E_R0(0);
    for (int i = 1; i < 49; i++)
    {
        E_R0[48 - i] = R0[32 - EP_Table[i - 1]];

        //debugging
        // if(i == 46) cout << "EP_Table[46 - 1] = " << EP_Table[45] << endl;
        // if(i == 47) cout << "EP_Table[47 - 1] = " << EP_Table[46] << endl;
        // if(i == 48) cout << "EP_Table[48 - 1] = " << EP_Table[47] << endl;
    }
    return E_R0;
}

int main()
{
    // Driver code
    bitset<64> example_message(0x0123456789ABCDEF);
    // cout << "Message in bits: " << example_message << endl;
    // cout << "L0 (after IP):   " << L0(example_message) << endl;
    cout << "R0 (after IP):   " << R0(example_message) << endl;

    // bitset<64> example_key(0x133457799BBCDFF1);
    // cout << "Key in bits: " << example_key << endl;
    // cout << "C0 (after PC1):   " << Key_PC1_Left(example_key) << endl;
    // cout << "D0 (after PC1):   " << Key_PC1_Right(example_key) << endl;

    // cout << "(Circular) left shift C0 by one: " << circularLeftShift(Key_PC1_Left(example_key), 1) << endl;
    // cout << "It should be:                    "
    //      << "1110000110011001010101011111" << endl;
    // cout << "(Circular) left shift C0 by two: " << circularLeftShift(Key_PC1_Left(example_key), 2) << endl;
    // cout << "(Circular) left shift D0 by one: " << circularLeftShift(Key_PC1_Right(example_key), 1) << endl;
    // cout << "It should be:                    "
    //      << "1010101011001100111100011110" << endl;

    // cout << "K1:           " << generate_subKey(circularLeftShift(Key_PC1_Left(example_key), 1), circularLeftShift(Key_PC1_Right(example_key), 1)) << endl;
    // cout << "K1 Should be: "
    //      << "000110110000001011101111111111000111000001110010" << endl;

    // Moving on...!

    // Expansion Permutation
    cout << "R0 (after EP):           " << expansionPermutation(R0(example_message)) << endl;
    cout << "R0 (after EP) should be: "
         << "011110100001010101010101011110100001010101010111" << endl;
    bitset <48> r0 ("011110100001010101010101011110100001010101010111");
    cout << "Differences:             " << (expansionPermutation(R0(example_message)) ^ (r0)) << endl;
}