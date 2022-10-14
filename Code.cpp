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

////////////////////////  Function block  /////////////////////////////////////
int expansionPermutation_Table[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

int P[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

int S1[64] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};
int S2[64] = {
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};
int S3[64] = {
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7};
int S4[64] = {
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};
int S5[64] = {
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};
int S6[64] = {
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};
int S7[64] = {
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};
int S8[64] = {
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

bitset<48> expansion_Permutation(bitset<32> old)
{
    bitset<48> result(0);
    for (int i = 1; i < 49; i++)
    {
        result[48 - i] = old[(32) - (EP_Table[(i - 1)])];
        // debugging
        if (i == 47)
        {
            // cout << "i: " << i <<  endl;
            // cout << "In EP_Table[i] = " << expansionPermutation_Table[i] << endl;
            // cout << "we should put old[i] = " << old[i] << endl;
            // cout << "But we put result[i] = " << result[i] << endl;
            cout << "At index " << i << endl;
            cout << "Data value: " << old[32-i] << endl;
            cout << "EP_Table[i] = " << EP_Table[i-1] << endl;
            //cout << "At the result index " << 48-i;
            //cout << "But it puts " << result[i] << "instead" << endl;
        }
    }
    return result;
};

// bitset<32> function_permutation(bitset<32> old) {
//     bitset<32> result(0);
//     for (int i = 0; i < 32; i++) {
//         result[i] = old[P[i] - 1];
//     }
//     return result;
// };

// bitset<6> function_s_box(bitset<6> old) {
//     // take 6 bits over 8 turns
//     bitset<32> result;
//     bitset<6> block;
//     for(int i = 0; i < 6; i += 6) {
//         block.reset();
//         for(int j = i ; j < i + 6; j++){
//             block[j - i] = old[j];
//         }
//         // convert outer bits to row (decimal), inner to column (decimal)
//         string str = block.to_string();
//         cout << "str: " << str << endl;
//         char first = str[0];
//         char second = str[1];
//         bitset<2> row(strcat(first, second));
//         bitset<4> col(str.substr(1, 4));
//         // int row = stoi(str.front() + str.back());
//         // int col = stoi(str.substr(1, 4));
//         cout << "row: " << row << endl;
//         cout << "col: " << col << endl;
//         for(int i = 0; i < 6; i++)
//             cout << i << " " << str[i] << endl;
//     }
//     return block;
//     // pick value by formula row *16 + column * 4
//     // convert value to binary and add to output in order
// };

int main()
{
    // bitset<6> x("100001");
    // cout << function_s_box(x) << endl;
    // bitset<32> x(0);
    // cout << "EP" << endl;
    // cout << "Old" << x << endl;
    // cout << "New" << function_expansion_permutation(x) << endl;
    // bitset<32> x(0);
    // x[15] = 1;
    // cout << "EP" << endl;
    // cout << "Old" << x << endl;
    // cout << "New" << function_permutation(x) << endl;

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
    bitset<48> EP_R0 = expansion_Permutation(R0(example_message));
    cout << "R0 (after EP):           " << EP_R0 << endl;
    
    // Example solution
    bitset<48> r0("011110100001010101010101011110100001010101010111");
    cout << "R0 (after EP) should be: " << r0 << endl;

    // Comparison
    cout << "Differences:             " << ((EP_R0) ^ (r0)) << endl;
}
