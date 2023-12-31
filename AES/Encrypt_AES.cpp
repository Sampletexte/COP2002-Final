#include <iostream>
#include <vector>
#include <string>

#include "AES.h"

using namespace std;


// vector<vector<int>> sbox = {
//         // 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
//         {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, //0
//         {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, //1
//         {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, //2
//         {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, //3
//         {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, //4
//         {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, //5
//         {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, //6
//         {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, //7
//         {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, //8
//         {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, //9
//         {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}, //A
//         {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, //B
//         {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, //C
//         {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, //D
//         {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, //E
//         {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}  //F
// };

// int Rcon[10] = {
//         0x01, 0x02, 0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,

// };


void AES::KeyGenerate(vector<vector<int>> finalkey) {
    vector<vector<int>> tempkey(4, vector<int> (4));

    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            // (a << 4) | b equal ab in binary
            tempkey[x][y] += ((rand() % 16) << 4) | (rand() % 16);
            finalkey[x][y] = tempkey[x][y];
        }
    }
};


// Takes in the key and returns the column at the index( the x value )
// vector<int> CreateWi(vector<vector<int>> finalkey, int idx){
//     vector<int> wi(4);
//     for(int x = 0; x < 4; x++)
//         wi[x] = finalkey[x][idx];

//     return wi;
// }

vector<int> AES::RotWord(vector<int> word)
{
    // Store the first value to move it to the bottom
    int first_val = word[0];
    // Shift the values up
    for(int i=0; i < 3; i++)
    {
        word[i] = word[i+1];
    }
    // Add value from front to the back
    word[3] = first_val;

    return word;
}

// Subsitutes bytes from the user input to the sbox using user input front and back nibbles( 4 bits in a byte )
// vector<int> MakeSubBytes(vector<int> user_input) {

//     for(int y = 0; y < 4; y++){
//         int sbox_x = user_input[y] >> 4;
//         int sbox_y = user_input[y] & 0xf;
//         user_input[y] = sbox[sbox_x][sbox_y];
//     }

//     return user_input;

// }


void AES::UseSubBytes(vector<vector<int>> &user_input){

    for(int x = 0; x < 4; x++){
        for (int y = 0; y < 4; y++) {
            int sbox_x = user_input[x][y] >> 4;
            int sbox_y = user_input[x][y] & 0xf;
            user_input[x][y] = sbox[sbox_x][sbox_y];
        }

    }

}


// returns the source WI
// vector<int> XorWi(vector<int> source, vector<int> second)
// {
//     for(int i=0; i < 4; i++)
//         source[i] ^= second[i];
//     return source;
// }


// void AddRoundKey(vector<vector<int>> *user_input ,vector<vector<int>>  *new_key, int start){
//     for(int i=0; i < 4; i++){
//         for (int j = 0; j < 4; j++){
//             int TMP = (*user_input)[i][j];
//             (*user_input)[i][j] = (*user_input)[i][j] ^ (*new_key)[i][start+j];
//         }
//     }
// }

// TEMPORARILY COMMENTED OUT AS IT DOES NOT DIRECTLY IMPACT THE ALGORITHM
// Converts the original text the user inputs, into the "user_input[4][4] array
vector<vector<int>> FourByFour(string orig_text){
    int counter = 0;
    vector<vector<int>> user_input(4, vector<int> (4));
    for(int i = 0; i < 4; i++){
        for(int j=0; j < 4; j++){
            orig_text[counter] = user_input[4][4];
            counter += 1;
        }
    }
    return user_input;
};


// vector<vector<int>> KeyExpand(vector<vector<int>> finalkey){
//     // Dynamically allocates memory for the new key. It may be better to use a vector for easier passing through functions and expansion.
//     vector<vector<int>> new_key(4, vector<int> (44));   // 44 columns due to the addition of the final key

//     // Assign final key to new final key
//     for(int y=0; y < 4; y++) {
//         for (int x = 0; x < 4; x++)
//             new_key[y][x] = finalkey[y][x];
//     }

//     int c_idx = 4;  // The current column being generated. Starts at 4 as that is the start after the origional key. (Arrays start from zero)

//     for(int round_num=0; round_num < 10; round_num++)
//     {
//         vector<int> rcon = {Rcon[round_num], 0,0,0};
//         vector<int> wi_1 = MakeSubBytes(RotWord(CreateWi(new_key, c_idx-1)));
//         vector<int> wi_4 = XorWi(CreateWi(new_key, c_idx-4), rcon);
//         vector<int> wi = XorWi(wi_1, wi_4);

//         for(int j=0; j < 4; j++) // Copy the wi column to the expanded key
//             new_key[j][c_idx] = wi[j];
//         c_idx++;

//         for(int i=0; i < 3; i++)
//         {
//             wi = XorWi(CreateWi(new_key, c_idx-1), CreateWi(new_key,c_idx-4));

//             for(int j=0; j < 4; j++) // Copy the wi column to the expanded key
//                 new_key[j][c_idx] = wi[j];
//             c_idx++;
//         }
//     }

//     return new_key;
// };

// For sub byting a 4-4 matrix
// void MakeSubBytes(vector<vector<int>> user_input){

//     for(int x = 0; x < 4; x++){
//         for (int y = 0; y < 4; y++) {
//             int sbox_x = user_input[x][y] >> 4;
//             int sbox_y = user_input[x][y] & 0xf;
//             user_input[x][y] = sbox[sbox_x][sbox_y];
//         }

//     }

// }

void AES::ShiftRows(vector<vector<int>> &user_input)
{
    for(int row_cnt=1; row_cnt < 4; row_cnt++)
    {
        for(int i=0; i < row_cnt; i++)
        {
            int popped_val = user_input[row_cnt][0];    // Get front value

            user_input[row_cnt].erase(user_input[row_cnt].begin()); // remove the first value and shift the rest of the row forward

            user_input[row_cnt].push_back(popped_val);    // Add popped value to the back of the row
        }
    }
};

// int GladiousMul(int a, int b)
// {
//     int p=0;

//     for(int i=0; i < 8; i++)
//     {
//         int a_high = a & 0x80;
//         if((b & 1) == 1)
//             p ^= a;

//         a <<= 1;

//         if(a_high == 0x80)
//             a ^= 0x1b;

//         b >>= 1;
//     }
//     return p & 0xff;    // Limit to 8 bits
// };

void AES::MixColumns(vector<vector<int>> &user_input) {
    for(int i=0; i < 4; i++) {
        vector<int> a = CreateWi(user_input, i);   // Get column
        int result[4];  // Doesn't exit the function. Thus no vector is needed

        // Matrix multiply by gladios field
        result[0] = GladiousMul(a[0], 2) ^ GladiousMul(a[1], 3) ^ GladiousMul(a[2], 1) ^ GladiousMul(a[3], 1);
        result[1] = GladiousMul(a[0], 1) ^ GladiousMul(a[1], 2) ^ GladiousMul(a[2], 3) ^ GladiousMul(a[3], 1);
        result[2] = GladiousMul(a[0], 1) ^ GladiousMul(a[1], 1) ^ GladiousMul(a[2], 2) ^ GladiousMul(a[3], 3);
        result[3] = GladiousMul(a[0], 3) ^ GladiousMul(a[1], 1) ^ GladiousMul(a[2], 1) ^ GladiousMul(a[3], 2);

        // Copy result to user input
        for(int j=0; j < 4; j++)
            user_input[j][i] = result[j];
    }
};


vector<vector<int>> AES::Encrypt(vector<vector<int>> &user_input,vector<vector<int>> &finalkey){
    vector<vector<int>> newkey = KeyExpand(finalkey);
    
    //Round 0
    AddRoundKey(&user_input, &newkey, 0);

    //Round 1-9
    for(int i = 1; i < 10; i++){
        UseSubBytes(user_input);
        ShiftRows(user_input);
        MixColumns(user_input);
        AddRoundKey(&user_input, &newkey ,(i * 4));
    }

    // Round 10 does not do the mix columns step as it is the final round
    UseSubBytes(user_input);
    ShiftRows(user_input);
    AddRoundKey(&user_input, &newkey , 40);


    return user_input;
}

string EncryptMain(string input)
{

};

// // THIS IS A DEBUG FUNCTION TO HELP ME VISUALIZE THE DATA AS IT HEADS THROUGH THE ALGORITHM
// void DebugDisplay(vector<vector<int>> &data)
// {
//     for (int i = 0; i < 4; i++) {
//         for (int j = 0; j < 4; j++) {
//             //std::cout << "I: " << i << " ~ " << hex <<  data[i][j] << " | ";
//             cout << hex <<  data[i][j] << " | ";
//         }
//         std::cout << std::endl;
//     }
//     cout << "";
// }


// int main() {
//     // Key used to test output
//     vector<vector<int>> finalkey = {
//             {0x2b, 0x28, 0xab, 0x09},
//             {0x7e, 0xae, 0xf7, 0xcf},
//             {0x15, 0xd2, 0x15, 0x4f},
//             {0x16, 0xa6, 0x88, 0x3c},
//     };

//     vector<vector<int>> test_input = {
//         {0x32, 0x88, 0x31, 0xe0},
//         {0x43, 0x5a, 0x31, 0x37},
//         {0xf6, 0x30, 0x98, 0x07},
//         {0xa8, 0x8d, 0xa2, 0x34}
//     };

//     //KeyGenerate(finalkey);
//     //vector<vector<int>> new_key = KeyExpand(finalkey);


//     vector<vector<int>> output = Cipher(test_input, finalkey);
    
//     cout << "Output: " << endl;
//     DebugDisplay(output);

//     //std::cout << "Hello, World!" << std::endl;
//     return 0;
// }