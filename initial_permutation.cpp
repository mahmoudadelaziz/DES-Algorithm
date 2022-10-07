/*
    -- WORK IN PROGRESS! --
*/

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    bitset <64> dataBlock (0x0123456789ABCDEF); // Example
    cout << "The message in binary: " << dataBlock << endl;
    cout << "The message inverted:  " << ~dataBlock << endl; //Just to be sure

    int IP_Table[64] = {}; //Indices for the Initial Permuation
}