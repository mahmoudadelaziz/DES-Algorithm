#include <iostream>
#include <fstream>

using namespace std;

typedef unsigned long long ull;

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
        dataBlock |= (ull) ch[7-i] << (8 * i);
        
        // Debugging (you could see the block filling up!)
        cout << "Iteration " << i+1 << ": ";
        for (int j = 0; j < 64; j++)
            cout << ((dataBlock & 1UL << (63 - j)) != 0);
        cout << endl;
    }

    return 0;
}