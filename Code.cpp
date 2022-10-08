/*
    -- WORK IN PROGRESS! --
    This is the main code file.
    All functions implemented in other code files
    must be integrated into this file in the end
    before we deliver the final executable.
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define DATABLOCK_BIT_LENGTH 64
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

// bitset<32> leftSide(bitset<64> ourData)
// {
//     // Returns the left side of our input plaintext data block
//     bitset<32> leftSide_data(ourData.to_string().substr(0, 32));
//     return leftSide_data;
// }

// bitset<32> rightSide(bitset<64> ourData)
// {
//     // Returns the right side of our input plaintext data block
//     bitset<32> rightSide_data(ourData.to_string().substr(32, 32));
//     return rightSide_data;
// }

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
        R0[32-i] = Data_after_IP[64 - IP_Table[32 + i - 1]];
    return R0;
}

int main()
{
    // string Word = "Universe";
    // cout << data_to_blocks(Word) << endl;
    // cout << leftSide(data_to_blocks(Word)) << endl;
    // cout << rightSide(data_to_blocks(Word)) << endl;

    bitset <64> example_message (0x0123456789ABCDEF);
    cout << "Message in bits: " << example_message << endl;
    cout << "L0 (after IP):   " << L0(example_message) << endl;
    cout << "R0 (after IP):   " << R0(example_message) << endl;
}