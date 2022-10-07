#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

int main ()
{
    bitset < 4 > bset1 (14);    //1110
    bitset < 4 > bset2 (7);     //0111
    cout << "bset1: " << (bset1) << endl;
    cout << "bset2: " << (bset2) << endl;
    
    cout << "bset1 AND bset2: " << (bset1 & bset2) << endl;
    cout << "bset1 OR bset2: " << (bset1 | bset2) << endl;
    cout << "bset1 XOR bset2: " << (bset1 ^ bset2) << endl;

    bitset <8> c1 ('A'); //A character
    cout << "The character in bitset c1: " << c1 << endl;

    return 0;
}
