#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

int main ()
{
    // bitset < 4 > bset1 (14);    //1110
    // bitset < 4 > bset2 (7);     //0111
    // cout << "bset1: " << (bset1) << endl;
    // cout << "bset2: " << (bset2) << endl;
    
    // cout << "bset1 AND bset2: " << (bset1 & bset2) << endl;
    // cout << "bset1 OR bset2: " << (bset1 | bset2) << endl;
    // cout << "bset1 XOR bset2: " << (bset1 ^ bset2) << endl;

    // bitset <8> c1 ('A'); //A character
    // cout << "The character in bitset c1: " << c1 << endl;
    // // This prints the binary of the character's ASCII code.
    
    // // Let's loop over bitset c1
    // for(int i = 0; i < 8; i++)
    // {
    //     cout << "Bit #" << i << " in c1: " << c1[i] << endl;
    // } //We see it counts from Least Significant Bit (LSB) to MSB 

    // // Input Plaintext
    // string word = "HELLO!";
    // //cout << word[0];

    // bitset <8> ch (word[1]);
    // cout << "The first character: " << ch << endl;

    // // Let's see if we can get a character from a bitset!
    // bitset <8> my_c (65); //A
    // cout << my_c.to_ulong() << endl;
    
    string word = "Hello there!";
    //bitset <64> PT (0);


        bitset <64> plainText {'H', 'e', 'l', 'l'};


    //cout << PT.to_string() << endl;
    return 0;
}
