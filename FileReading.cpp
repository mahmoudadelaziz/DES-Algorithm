#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long long u64;

int IP_Table[64] =
    {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7}; // Indices for the Initial Permuation

u64 do_initial_permutation(u64 M)
{
    u64 result = 0;
    for (int i = 0; i < 64; ++i)
        result |= (M >> (64 - IP_Table[i]) & 1) << 64 - (i + 1);
    return result;
}

int main()
{
    // Declare a file variable
    ifstream input_data;
    // Open the file
    input_data.open("./sample.txt");

    u64 dataBlock = 0;
    /* Trying out initial permutation */
    u64 message = 0x0123456789ABCDEF; // from example
    u64 result = 0;

    cout << "Message:   ";
    for (int i = 0; i < 64; i++)
        cout << ((message & 1UL << (63 - i)) != 0);

    u64 IP_result = do_initial_permutation(message);

    cout << "\nafter IP:  ";
    for (int i = 0; i < 64; i++)
        cout << ((IP_result & 1UL << (63 - i)) != 0);

    cout << "\nshould be: 1100110000000000110011001111111111110000101010101111000010101010";

    return 0;
}