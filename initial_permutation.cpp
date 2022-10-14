/*
    -- WORK IN PROGRESS! --
    Walking through the example at:
    https://captanu.wordpress.com/2015/04/05/des/
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    bitset<64> dataBlock("0000000100100011010001010110011110001001101010111100110111101111"); // Example
    cout << "The message in binary (before IP): " << dataBlock << endl;

    int IP_Table[64] =
        {
            58,    50,   42,    34,    26,   18,    10,    2,
            60,    52,   44,    36,    28,   20,    12,    4,
            62,    54,   46,    38,    30,   22,    14,    6,
            64,    56,   48,    40,    32,   24,    16,    8,
            57,    49,   41,    33,    25,   17,     9,    1,
            59,    51,   43,    35,    27,   19,    11,    3,
            61,    53,   45,    37,    29,   21,    13,    5,
            63,    55,   47,    39,    31,   23,    15,    7
        }; // Indices for the Initial Permuation

    // Performing IP
    bitset<64> data_after_IP(0);
    bitset<32> L0 (0);
    bitset<32> R0 (0);

    for (int i = 1; i < 65; i++)
    {
        data_after_IP[64 - i] = dataBlock[64 - IP_Table[i - 1]]; //Redundant?
        L0[32-i] = dataBlock[32 - IP_Table[i - 1]];
        R0[32-i] = dataBlock[64 - IP_Table[32 + i - 1]];
    }

    // Working through the example
    bitset<64> ex_after_IP("1100110000000000110011001111111111110000101010101111000010101010");
    cout << "The message  (after IP): " << data_after_IP << endl;
    cout << "It should be (after IP): " << ex_after_IP << endl;
    cout << "Am I right?              " << ~((~data_after_IP) & ex_after_IP) << endl;

    cout << "L0: " << L0 << endl;
    cout << "R0: " << R0 << endl;
}