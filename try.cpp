/*
    This file is just for trial and error.
    Feel free to experiment here.
*/ 

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define BIT_ARRAY_LENGTH 64

int main()
{
    // Example string
    string plainText = "Caesar needs to lose weight.";

    // We wish to operate on 8-bit blocks of this string.
    bitset<8> x0(plainText[0]);
    cout << "The first character in 8 bits: " << x0 << endl;

    // Let's try adding bitsets
    bitset<8> x1(plainText[1]);
    cout << "The second character in 8 bits: " << x1 << endl;

    bitset <16> x01 (x0.to_string() + x1.to_string());
    cout << "The two characters put together in 16 bits: " << (x01) << endl;
    x01[0] = 1; //bit altering (0 index is the LSB (rightmost))
    cout << "The two characters put together in 16 bits (altered 1st bit): " << (x01) << endl; 

    // Making 64-bit blocks of data from the string
    string myPlainText = "Habibi yasta";
    bitset <64> myBlock (0x0000);
    string binaryBlock;
    cout << "initial block: " << myBlock << endl;

    for(int i = 0; i < 8; i++)
    {
        bitset <8> ch (myPlainText[i]);
        binaryBlock += ch.to_string();
    }

    bitset <64> ourBlock (binaryBlock);
    cout << "Populated block (as string): " << binaryBlock << endl;
    cout << "Populated block (as bitset): " << ourBlock << endl;
    cout << "Populated block (Inverted): " << ~ourBlock << endl;

    // Let's try this: create

    return 0;
}