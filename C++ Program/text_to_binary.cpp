#include <iostream>
#include <bits/stdc++.h>

using namespace std;

#define DATABLOCK_BIT_LENGTH 64

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

bitset<32> leftSide(bitset<64> ourData)
{
    // Returns the left side of our input plaintext data block
    bitset <32> leftSide_data(ourData.to_string().substr(0, 32));
    return leftSide_data;
}

bitset<32> rightSide(bitset<64> ourData)
{
    // Returns the right side of our input plaintext data block
    bitset <32> rightSide_data(ourData.to_string().substr(32, 32));
    return rightSide_data;
}

int main()
{

    string Word = "Universe";
    cout << data_to_blocks(Word) << endl;
    cout << leftSide(data_to_blocks(Word)) << endl;
    cout << rightSide(data_to_blocks(Word)) << endl;

    // Transform input text (plaintext) to 64-bit blocks

    // // Input string (plaintext)
    // string plainText;
    // cin >> plainText;
    // // Initiate binary string
    // string binaryString;
    // for (int i = 0; i < 8; i++)
    // {
    //     bitset<8> ch(plainText[i]);
    //     binaryString += ch.to_string();
    // }

    // bitset<64> dataBlock(binaryString);

    // cout << "The word is:   " << plainText << endl;
    // cout << "In bits:       " << dataBlock << endl;

    // // Divide into two equal halves
    // bitset<32> leftSide_data(binaryString.substr(0, 32));
    // bitset<32> rightSide_data(binaryString.substr(32, 32));

    // // test
    // bitset<32> testing(0x00);

    // cout << "The right side of the data block: " << rightSide_data << endl;
    // cout << "The left side of the data block:  " << leftSide_data << endl;

    // cout << "Size of our data block = " << dataBlock.size() << " bits." << endl;
    // cout << "Size of each side = " << testing.size() << " bits." << endl;
}