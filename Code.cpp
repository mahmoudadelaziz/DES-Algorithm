/*
    -- WORK IN PROGRESS! --
    This is the main code file.
    All functions implemented in other code files
    must be integrated into this file in the end
    before we deliver the final executable.
    >> Walking through the example at:
    https://page.math.tu-berlin.de/~kant/teaching/hess/krypto-ws2006/des.htm
*/

#include <iostream>

using namespace std;

typedef unsigned long long u64;

/* --------------- DEFINING GLOBAL VARIABLES --------------- */

int PC1_Table[56] =
    {57, 49, 41, 33, 25, 17, 9,
     1, 58, 50, 42, 34, 26, 18,
     10, 2, 59, 51, 43, 35, 27,
     19, 11, 3, 60, 52, 44, 36,
     63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
     14, 6, 61, 53, 45, 37, 29,
     21, 13, 5, 28, 20, 12, 4}; // list of indices

int PC2_Table[48] =
    {14, 17, 11, 24, 1, 5,
     3, 28, 15, 6, 21, 10,
     23, 19, 12, 4, 26, 8,
     16, 7, 27, 20, 13, 2,
     41, 52, 31, 37, 47, 55,
     30, 40, 51, 45, 33, 48,
     44, 49, 39, 56, 34, 53,
     46, 42, 50, 36, 29, 32};

int shifts[16] = {1, 2, 4, 6, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27, 28};

// Indices for the Initial Permuation
int IP_Table[64] =
    {
        58, 50, 42, 34, 26, 18, 10, 2,
        60, 52, 44, 36, 28, 20, 12, 4,
        62, 54, 46, 38, 30, 22, 14, 6,
        64, 56, 48, 40, 32, 24, 16, 8,
        57, 49, 41, 33, 25, 17, 9, 1,
        59, 51, 43, 35, 27, 19, 11, 3,
        61, 53, 45, 37, 29, 21, 13, 5,
        63, 55, 47, 39, 31, 23, 15, 7};

// Indices for Inverse Permutation
int inversePermutation[64] =
    {40, 8, 48, 16, 56, 24, 64, 32,
     39, 7, 47, 15, 55, 23, 63, 31,
     38, 6, 46, 14, 54, 22, 62, 30,
     37, 5, 45, 13, 53, 21, 61, 29,
     36, 4, 44, 12, 52, 20, 60, 28,
     35, 3, 43, 11, 51, 19, 59, 27,
     34, 2, 42, 10, 50, 18, 58, 26,
     33, 1, 41, 9, 49, 17, 57, 25};

int EP_Table[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1};

int simplePermutation_table[32] = {
    16, 7, 20, 21,
    29, 12, 28, 17,
    1, 15, 23, 26,
    5, 18, 31, 10,
    2, 8, 24, 14,
    32, 27, 3, 9,
    19, 13, 30, 6,
    22, 11, 4, 25};

int S1[64] = {
    14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
    0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
    4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
    15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13};
int S2[64] = {
    15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
    3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
    0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
    13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9};
int S3[64] = {
    10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
    13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
    1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12,
    13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7};
int S4[64] = {
    7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
    13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
    10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
    3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14};
int S5[64] = {
    2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
    14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
    4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
    11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3};
int S6[64] = {
    12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
    10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
    9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
    4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13};
int S7[64] = {
    4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
    13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
    1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
    6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12};
int S8[64] = {
    13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
    1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
    7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
    2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11};

// Make an array of S-boxes to iterate through
int *SBox_number[8] = {S1, S2, S3, S4, S5, S6, S7, S8};

/* --------------- DEFINING GLOBAL VARIABLES COMPLETE --------------- */

/* ------------------ DEFINING HELPER FUNCTIONS --------------------------- */

u64 Key_PC1(u64 fullKey)
{
    /* takes the full 64-bit key,
    and returns a 56-bit key by moving around the bits of the full key. */
    u64 newKey = 0;
    for (int i = 0; i < 56; i++)
        newKey |= (fullKey >> (64 - PC1_Table[56 - 1 - i]) & 1) << i;
    return newKey;
}

int left_shift(int halfkey, int n)
{
    /* Performs bit left-shifting on Cn or Dn by the appropriate n */
    halfkey = (((halfkey << n) | (halfkey >> (28 - n))) & 0x000000000FFFFFFFLL);
    return halfkey;
}

u64 Key_PC2(u64 CnDn)
{
    /* takes the CnDn (after bit-rotation),
    and returns a 48-bit subkey for the current DES round. */
    u64 newKey = 0;
    for (int i = 0; i < 48; i++)
        newKey |= (CnDn >> (56 - PC2_Table[48 - 1 - i]) & 1) << i;
    return newKey;
}

u64 do_initial_permutation(u64 M)
{
    u64 result = 0;
    for (int i = 0; i < 64; ++i)
        result |= (M >> (64 - IP_Table[i]) & 1) << 64 - (i + 1);
    return result;
}

u64 do_expansion_permutation(int Rn)
{
    /* takes 32-bits of date and expand them into 48-bits #expanded_permutation */
    u64 newExpData = 0;
    for (int i = 0; i < 48; i++)
        newExpData |= (Rn >> (48 - EP_Table[48 - 1 - i]) & 1ULL) << i;
    return newExpData;
}

int do_SBox(u64 input)
{
    /* Takes 48-bit input of (E(Rn) XOR Kn),
    to give you 32-bit output of the SBoxes */
    int result = 0;
    int val_selector = 0;
    int row = 0;
    int column = 0;
    int box_no = 0;

    for (int i = 0; i < 8; i++)
    {
        // Selects the 6-bit value which will determine the index
        val_selector = (input & (0x0000003FULL << 6 * i)) >> (6 * i);
        row = ((val_selector >> 5) << 1) | (val_selector & 1);
        column = (val_selector >> 1) & 0x0000000F;
        box_no = 7 - i;

        result |= ((SBox_number[box_no][row * 16 + column]) << (28 - (7 - i) * 4));
    }
    return result;
}

int do_simple_permutation(int M)
{
    int result = 0;
    for (int i = 0; i < 32; ++i)
        result |= (M >> (32 - simplePermutation_table[i]) & 1) << 32 - (i + 1);
    return result;
}

u64 get_Subkey(u64 inputKey, int round_no)
{
    u64 Kn = 0;
    u64 K_after_PC1 = Key_PC1(inputKey);
    // Get C0 and D0
    unsigned int C0 = 0;
    unsigned int D0 = 0;
    C0 = int((K_after_PC1 & 0x00FFFFFFF0000000LL) >> 28);
    D0 = int((K_after_PC1 & 0x000000000FFFFFFFLL));
    int Cn = 0;
    int Dn = 0;
    Cn = left_shift(C0, shifts[round_no]);
    Dn = left_shift(D0, shifts[round_no]);
    // Get CnDn
    u64 subkey_before_PC2 = ((u64)Cn) << 28 | Dn;
    // Get Kn
    Kn = Key_PC2(subkey_before_PC2);
    return Kn;
}

// u64 ENCRYPT(u64 PT_block, u64 *allSubkeys)
// {

//     u64 CT_block = 0;

//     // ------ First round (one time operations) ----------
//     // ------ On Plaintext --------
//     u64 after_IP = do_initial_permutation(PT_block);
//     uint L0 = uint((after_IP & 0xFFFFFFFF00000000ULL) >> 32);
//     uint R0 = uint((after_IP & 0x00000000FFFFFFFFULL));

//     // 16 rounds of encryption
//     for (int i = 0; i < 16; i++)
//     {
//         // Do expansion perm to get E(R0)
//         u64 E_R0 = do_expansion_permutation(R0);

//         // Get Kn

//     }

//     return CT_block;
// }

int main()
{

    //######## GET ARRAY OF KEYS ############
    u64 ex_key = 0x133457799BBCDFF1; //input key
    u64 subkeys_arr[16];
    for (int i = 0; i < 16; i++)
    {
        subkeys_arr[i] = get_Subkey(ex_key, i);
        // Show results
        cout << "K" << (i + 1) << " = ";
        for (int j = 0; j < 48; j++)
            cout << ((subkeys_arr[i] & 1ULL << (47 - j)) != 0);
        cout << endl;
    }
    //######## GET ARRAY OF KEYS ############

    // ############# STEP BY STEP @@@@@@@@@@@@@@@@@@@@@@@
    // u64 example_message = 0x0123456789ABCDEF;
    // // Initial Permutation
    // u64 after_IP = do_initial_permutation(example_message);
    // // (Show result)
    // cout << "IP_M:  ";
    // for (int i = 0; i < 64; i++)
    //     cout << ((after_IP & 1UL << (63 - i)) != 0);

    // // Get L0 and R0
    // uint L0 = uint((after_IP & 0xFFFFFFFF00000000ULL) >> 32);
    // uint R0 = uint((after_IP & 0x00000000FFFFFFFFULL));
    // // (Show result)
    // cout << "\nL0:  ";
    // for (int i = 0; i < 32; i++)
    //     cout << ((L0 & 1UL << (31 - i)) != 0);
    // cout << "\nR0:  ";
    // for (int i = 0; i < 32; i++)
    //     cout << ((R0 & 1UL << (31 - i)) != 0);

    // // L1 = R0
    // // R1 = L0 + f(R0, K1)
    // // So, let's perform f

    // // Do expansion perm to get E(R0)
    // u64 E_R0 = do_expansion_permutation(R0);
    // // Show result
    // cout << "\nE(R0):  ";
    // for (int i = 0; i < 64; i++)
    //     cout << ((E_R0 & 1UL << (63 - i)) != 0);
    // cout << endl;

    // // Get E(R0) XOR K1
    // u64 K1 = 0x1B02EFFC7072;
    // u64 R0_XOR_K1 = E_R0 ^ K1;
    // // Show result
    // cout << "input to SBoxes: ";
    // for (int i = 0; i < 64; i++)
    //     cout << ((R0_XOR_K1 & 1UL << (63 - i)) != 0);

    // // Now S-boxes!
    // // Let's try S-value selectors (6-bits each)
    // int after_SBox_1 = do_SBox(R0_XOR_K1);
    // // Show result
    // cout << "\nAfter SBox: ";
    // for (int i = 0; i < 32; i++)
    //     cout << ((after_SBox_1 & 1UL << (31 - i)) != 0);

    // // Moving on after S-Boxes...
    // // Normal 32-to-32 permutation...
    // int F_R0_K1 = do_simple_permutation(after_SBox_1);
    // // Show result
    // cout << "\nFinally, F(R0, K1) = ";
    // for (int i = 0; i < 32; i++)
    //     cout << ((F_R0_K1 & 1UL << (31 - i)) != 0);

    // // R1 = L0 + f(R0, K1)
    // uint R1 = (L0 + F_R0_K1);
    // // Show result
    // cout << "\nR1 = ";
    // for (int i = 0; i < 32; i++)
    //     cout << ((R1 & 1 << (31 - i)) != 0);
    // ############# STEP BY STEP @@@@@@@@@@@@@@@@@@@@@@@

    return 0;
}