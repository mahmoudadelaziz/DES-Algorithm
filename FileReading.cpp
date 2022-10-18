#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long long ull;

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

int main()
{
    // Declare a file variable
    ifstream input_data;

    // Open the file
    input_data.open("./sample.txt");

    // Read an array of 8 characters (64-bit data block)
    char ch[8];
    for (int i = 0; i < 8; i++)
    {
        ch[i] = input_data.get();
        cout << ch[i];
    }

    ull dataBlock = 0;
    cout << "\nSize of dataBlock = " << sizeof(dataBlock) << " bytes." << endl;

    for (int i = 0; i < 8; i++)
    {
        // Characters in reverse order from the array
        dataBlock |= (ull)ch[7 - i] << (8 * i);

        // Debugging (you could see the block filling up!)
        cout << "Iteration " << i + 1 << ": ";
        for (int j = 0; j < 64; j++)
            cout << ((dataBlock & 1UL << (63 - j)) != 0);
        cout << endl;
    }

    /* Trying out initial permutation */
    ull message = 0x0123456789ABCDEF; // from example
    ull result = 0;

    for (int i = 0; i < 64; i++)
        result |= (((message & 1UL << (IP_Table[i] - 1)) != 0) << i);

    cout << "Message: ";
    for (int i = 0; i < 64; i++)
        cout << ((message & 1UL << (63 - i)) != 0);

    cout << "\nafter IP: \n";
    for (int i = 0; i < 64; i++)
        cout << ((result & 1UL << (63 - i)) != 0);

    return 0;
}