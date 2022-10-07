#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define BIT_ARRAY_LENGTH 64

int main()
{
    // Transform input text (plaintext) to 64-bit blocks

    // Input string (plaintext)
    string plainText;
    cin >> plainText;
    // Initiate binary string
    string binaryString;
    for (int i = 0; i < 8; i++)
    {
        bitset<8> ch(plainText[i]);
        binaryString += ch.to_string();
    }
    
    bitset <64> dataBlock(binaryString);

    cout << "The word is:   " << plainText << endl;
    cout << "In bits:       " << dataBlock << endl;

    // Divide into two equal halves
    bitset <32> leftSide_data(binaryString.substr(0,32));
    bitset <32> rightSide_data(binaryString.substr(32,32));

    //test
    bitset <32> testing (0x00);

    cout << "The right side of the data block: " << rightSide_data << endl;
    cout << "The left side of the data block:  " << leftSide_data << endl;

    cout << "Size of our data block = " << dataBlock.size() << " bits." << endl;
    cout << "Size of each side = " << testing.size() << " bits." << endl;
}