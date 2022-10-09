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
    x01[0] = 0; //bit altering (0 index is the LSB (rightmost))
    cout << "The two characters put together in 16 bits (altered 1st bit): " << (x01) << endl; 

    // Making 64-bit blocks of data from the string
    string myPlainText = "Habibi yasta";
    bitset <64> myBlock (0x0000);
    string binaryBlock;
    cout << "initial block: " << myBlock << endl;

    for(int i = 0; i < 8; i++)
    {
        //bitset <8> ch (myPlainText[i]);
        //binaryBlock += ch.to_string();

        myBlock[i] = 5;
        
    }

    //bitset <64> ourBlock (binaryBlock);
    //cout << "Populated block (as string): " << binaryBlock << endl;
    cout << "Populating the empty bitset: " << myBlock << endl;
    //cout << "Populated block (as bitset): " << ourBlock << endl;
    //cout << "Populated block (Inverted):  " << ~ourBlock << endl;

    // Let's try this: create

    /* --------------------------------------------------------------------- */
    cout << "-------------------------------------------------" << endl;
    cout << "-------------------------------------------------" << endl;

    int pc1[56] = {
	57,49,41,33,25,17,9, 
	1,58,50,42,34,26,18, 
	10,2,59,51,43,35,27, 
	19,11,3,60,52,44,36,		 
	63,55,47,39,31,23,15, 
	7,62,54,46,38,30,22, 
	14,6,61,53,45,37,29, 
	21,13,5,28,20,12,4 
	};

    // Take the key from User
    //int ipKey;
    //cin >> hex >> ipKey;

    // Hard-coded key for now
    bitset <64> ourKey (0x133457799BBCDFF1);

    //cout << "User input: " << ipKey << endl;
    cout << "Our bitset: " << ourKey << endl;

    return 0;
}