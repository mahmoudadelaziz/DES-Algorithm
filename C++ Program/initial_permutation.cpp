#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int main()
{
    string plainText = "0000000100100011010001010110011110001001101010111100110111101111";
    bitset <64> dataBlock (plainText);
    cout << "The message in binary: " << dataBlock << endl;
    cout << "The message inverted:  " << ~dataBlock << endl; //Just to be sure

    int IP_Table[64] = {};
}