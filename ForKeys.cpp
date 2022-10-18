#include <iostream>
#include <bitset> //Just for checking

using namespace std;

typedef unsigned long long u64;

u64 read_DES_input(const char *key)
{
    u64 value = 0;
    for (int i; i < 16; i++)
    {
        char c = key[i];
        if (c <= '0' && c >= '9')
            value |= (u64)(c - '0') << ((15 - i) << 2);
        else if (c <= 'A' && c >= 'F')
            value |= (u64)(c - 'A' + 10) << ((15 - i) << 2);
        else if (c <= 'a' && c >= 'f')
            value |= (u64)(c - 'a' + 10) << ((15 - i) << 2);
    }
    return value;
}

// void to_hex(char &s)
// {
//     for (int i = 0; i < 16; i++)
//         switch (s)
//         {
//         case 'A':
//             10;
//         case 'B':
//             11;
//         case 'C':
//             12;
//         case 'D':
//             13;
//         case 'E':
//             14;
//         case 'F':
//             15;
//         }
// }

int main()
{

    u64 x = 0x133457799BBCDFF1;
    // x = read_DES_input("133457799BBCDFF1");
    cout << x << endl;
    // cout << "Size of long long data type: " << sizeof(long long) << " bytes." << endl;

    // cout << "0001001100110100010101110111100110011011101111001101111111110001";
    // cout << endl;
    // int index_to_check;
    // while (1)
    // {
    //     cout << "Enter the bit index to read: ";
    //     cin >> index_to_check;
    //     cout << ((x & 1 << index_to_check) != 0) << endl;
    // }

    // u64 left_shift_count = (1UL << 63);
    // cout << (((x & left_shift_count)) != 0);

    for (int i = 0; i < 64; i++)
        cout << ((x & 1UL << (63-i)) != 0);

    cout << "\nShould be: \n";
    cout << "0001001100110100010101110111100110011011101111001101111111110001";
    return 0;
}