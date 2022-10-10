typedef struct Edge_permutations
{
    int INITIAL_PERMUTATION[8][8];
    int FINAL_PERMUTATUION[8][8];
} Edge_permutations;

typedef struct F_function
{
    int EXPANSION_PERMUTATION[8][6];
    int S_BOX_1[4][16];
    int S_BOX_2[4][16];
    int S_BOX_3[4][16];
    int S_BOX_4[4][16];
    int S_BOX_5[4][16];
    int S_BOX_6[4][16];
    int S_BOX_7[4][16];
    int S_BOX_8[4][16];
    int PERMUTATION[4][8];
} F_function;

typedef struct key_schedule
{
    int INITIAL_PERMUTATION[7][8];
    int ROUND_KEY_PERMUTATION[6][8];
} Key;
