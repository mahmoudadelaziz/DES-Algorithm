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
    bitset<64> dataBlock(0x0123456789ABCDEF); // Example
    cout << "The message in binary: " << dataBlock << endl;
    cout << "The message inverted:  " << ~dataBlock << endl; // Just to be sure

    int IP_Table[64] =
        {57, 49, 41, 33, 25, 17, 9,
         1, 58, 50, 42, 34, 26, 18,
         10, 2, 59, 51, 43, 35, 27,
         19, 11, 3, 60, 52, 44, 36,
         63, 55, 47, 39, 31, 23, 15,
         7, 62, 54, 46, 38, 30, 22,
         14, 6, 61, 53, 45, 37, 29,
         21, 13, 5, 28, 20, 12, 4}; // Indices for the Initial Permuation

         
}