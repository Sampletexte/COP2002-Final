#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>


using namespace std;


class Ceaser


{
    public:
    int shift_value;
    string encoded_string = "";
        basic_string<char> Encrypt(string input_text)
        {

            while(1)
            {
                shift_value = 1 + rand()%26;
                if(shift_value != 26)
                    break;
            };

            ofstream my_file;
            my_file.open("Key.txt", ios::out);
            my_file << shift_value;
            my_file.close();

            for(int i=0; i < input_text.length(); i++)
            {
                char letter = tolower(input_text[i]);
                if(letter >= 'a' && 'z' >= letter) {
                    char letter = tolower(input_text[i]);
                    char shifted_letter = (letter - 'a' + shift_value) % 26 ;

                    encoded_string += (shifted_letter + 'a');
                } else {
                    encoded_string += (input_text[i]);


                };

            };
            my_file.open("Encrypted.txt", ios::out);
            my_file << encoded_string;
            my_file.close();
            vector<string> ret_arr = {encoded_string, to_string(shift_value)};

            return encoded_string;
        };

        string Decrypt(string input_text, int key)
        {
            (key);

            string decoded_string;

            for(int i=0; i < input_text.length(); i++)
            {
                char letter = tolower(input_text[i]);
                if(letter >= 'a' && 'z' >= letter) {
                    char shifted_letter = letter - shift_value;

                    // Wrap the letter between a and z
                    int offset = mod(shifted_letter - 'a', 26);
                    decoded_string += offset + 'a';
                } else {
                    decoded_string += input_text[i];
                };
            };
            ofstream my_file;
            my_file.open("Decrypt.txt", ios::out);
            my_file << decoded_string;
            my_file.close();

            // Save encrypted text
            return decoded_string;
        };

    private:
    // Functions here
        static int mod(int val, int max_val)
        {
            if( val < 0 ) {
                return max_val + val;
            } else if( max_val <= val ) {
                return val-max_val;
            };
            return val;
        };
    ;
};


class Vigenere{
public:
// Generate a random Key of random length
    string KeyGenerate(string user_input){
        string randkey;
        string finalkey;
        int length = 2 + rand()%7;
        for(int i = 0; i < length ; i++){
            randkey += 'a' + rand()%26;

        };
// Have the key loop until it meets length of the user-inputting string
        int full_loops = user_input.length() / randkey.length();
        int remainder = user_input.length() % randkey.length();
        string tempkey = "";
        for(int i = 0; i < full_loops; i++) {
            tempkey += randkey;
        }
        for(int i = 0; i < remainder; i++){
            tempkey += randkey[i];
        }
        finalkey = tempkey;
        return finalkey;
    };


     string Encrypt(string x,string key){
         string newtext = "";
        for(int i = 0; i < x.length(); i++){
            if(x[i] == ' '){
                newtext.push_back(' ');
            }
            else{

            char temp = (x[i] + key[i] -(2 * 'a')) % 26;
            newtext.push_back(temp + 'a' );};




    }return newtext;
     };

    string Decrypt(string y,string key){
        string newtext = "";
        for(int i = 0; i < y.length(); i++){
            if(y[i]== ' '){
                newtext.push_back(' ');
            }
            else {
                char temp = (y[i] - key[i] + 26) % 26;
                newtext.push_back(temp + 'a');
            }
        }return newtext;

    };
};


class AES
{
    vector<vector<int>> sbox = {
            // 0     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F
            {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76}, //0
            {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0}, //1
            {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15}, //2
            {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75}, //3
            {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84}, //4
            {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf}, //5
            {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8}, //6
            {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2}, //7
            {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73}, //8
            {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb}, //9
            {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79}, //A
            {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08}, //B
            {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a}, //C
            {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e}, //D
            {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf}, //E
            {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}  //F
    };

    const int Rcon[10] = {
            0x01, 0x02, 0x04,0x08,0x10,0x20,0x40,0x80,0x1b,0x36,
    };


    // Takes in the key and returns the column at the index( the x value )
    vector<int> CreateWi(vector<vector<int>> finalkey, int idx){
        vector<int> wi(4);
        for(int x = 0; x < 4; x++)
            wi[x] = finalkey[x][idx];

        return wi;
    }


    void AddRoundKey(vector<vector<int>> *user_input ,vector<vector<int>>  *new_key, int start){
        for(int i=0; i < 4; i++){
            for (int j = 0; j < 4; j++){
                int TMP = (*user_input)[i][j];
                int TMP2 = (*user_input)[i][j] ^ (*new_key)[i][start+j];
                (*user_input)[i][j] = (*user_input)[i][j] ^ (*new_key)[i][start+j];
            }
        }
    }


    // returns the source WI
    vector<int> XorWi(vector<int> source, vector<int> second)
    {
        for(int i=0; i < 4; i++)
            source[i] ^= second[i];
        return source;
    }


    vector<vector<int>> KeyExpand(vector<vector<int>> finalkey){
        // Dynamically allocates memory for the new key. It may be better to use a vector for easier passing through functions and expansion.
        vector<vector<int>> new_key(4, vector<int> (44));   // 44 columns due to the addition of the final key

        // Assign final key to new final key
        for(int y=0; y < 4; y++) {
            for (int x = 0; x < 4; x++)
                new_key[y][x] = finalkey[y][x];
        }

        int c_idx = 4;  // The current column being generated. Starts at 4 as that is the start after the origional key. (Arrays start from zero)

        for(int round_num=0; round_num < 10; round_num++)
        {
            vector<int> rcon = {Rcon[round_num], 0,0,0};
            vector<int> wi_1 = MakeSubBytes(InvRotWord(CreateWi(new_key, c_idx-1)));
            vector<int> wi_4 = XorWi(CreateWi(new_key, c_idx-4), rcon);
            vector<int> wi = XorWi(wi_1, wi_4);

            for(int j=0; j < 4; j++) // Copy the wi column to the expanded key
                new_key[j][c_idx] = wi[j];
            c_idx++;

            for(int i=0; i < 3; i++)
            {
                wi = XorWi(CreateWi(new_key, c_idx-1), CreateWi(new_key,c_idx-4));

                for(int j=0; j < 4; j++) // Copy the wi column to the expanded key
                    new_key[j][c_idx] = wi[j];
                c_idx++;
            }
        }

        return new_key;
    };


    // Subsitutes bytes from the user input to the sbox using user input front and back nibbles( 4 bits in a byte )
    vector<int> MakeSubBytes(vector<int> user_input) {

        for(int y = 0; y < 4; y++){
            int sbox_x = user_input[y] >> 4;
            int sbox_y = user_input[y] & 0xf;
            user_input[y] = sbox[sbox_x][sbox_y];
        }

        return user_input;

    }


    int GladiousMul(int a, int b)
    {
        int p=0;

        for(int i=0; i < 8; i++)
        {
            int a_high = a & 0x80;
            if((b & 1) == 1)
                p ^= a;

            a <<= 1;

            if(a_high == 0x80)
                a ^= 0x1b;

            b >>= 1;
        }
        return p & 0xff;    // Limit to 8 bits
    };



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


    vector<int> RotWord(vector<int> word)
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


    void UseSubBytes(vector<vector<int>> &user_input){

        for(int x = 0; x < 4; x++){
            for (int y = 0; y < 4; y++) {
                int sbox_x = user_input[x][y] >> 4;
                int sbox_y = user_input[x][y] & 0xf;
                user_input[x][y] = sbox[sbox_x][sbox_y];
            }

        }

    }


    void ShiftRows(vector<vector<int>> &user_input)
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


    void MixColumns(vector<vector<int>> &user_input) {
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




    vector<vector<int>> invs_sbox = {
            {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
            {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
            {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
            {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
            {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
            {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
            {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
            {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
            {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
            {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
            {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
            {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
            {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
            {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
            {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
            {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
    };


    void InvUseSubBytes(vector<vector<int>> &user_input){

        for(int x = 0; x < 4; x++){
            for (int y = 0; y < 4; y++) {
                int invs_sbox_x = user_input[x][y] >> 4;
                int invs_sbox_y = user_input[x][y] & 0xf;
                user_input[x][y] = invs_sbox[invs_sbox_x][invs_sbox_y];
            }

        }

    }


    vector<int> InvRotWord(vector<int> word)
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


    void InvShiftRows(vector<vector<int>> &user_input)
    {
        for(int row_cnt=1; row_cnt < 4; row_cnt++)
        {
            for(int i=0; i < row_cnt; i++)
            {
                int popped_val = user_input[row_cnt][3];    // Get back value

                user_input[row_cnt].erase(user_input[row_cnt].begin()+3); // remove the last value

                user_input[row_cnt].insert(user_input[row_cnt].begin(), popped_val);    // Add popped value to the front of the row
            }
        }
    };


    void InvMixColumns(vector<vector<int>> &user_input) {
        for(int i=0; i < 4; i++) {
            vector<int> a = CreateWi(user_input, i);   // Get column
            int result[4];  // Doesn't exit the function. Thus no vector is needed


            // Matrix multiply by gladios field
            result[0] = GladiousMul(a[0], 0x0e) ^ GladiousMul(a[1], 0x0b) ^ GladiousMul(a[2], 0x0d) ^ GladiousMul(a[3], 0x09);
            result[1] = GladiousMul(a[0], 0x09) ^ GladiousMul(a[1], 0x0E) ^ GladiousMul(a[2], 0x0b) ^ GladiousMul(a[3], 0x0d);
            result[2] = GladiousMul(a[0], 0x0d) ^ GladiousMul(a[1], 0x09) ^ GladiousMul(a[2], 0x0e) ^ GladiousMul(a[3], 0x0b);
            result[3] = GladiousMul(a[0], 0x0b) ^ GladiousMul(a[1], 0x0d) ^ GladiousMul(a[2], 0x09) ^ GladiousMul(a[3], 0x0e);

            // Copy result to user input
            for(int j=0; j < 4; j++)
                user_input[j][i] = result[j];
        }
    };

    vector<vector<int>> Encrypt(vector<vector<int>> &user_input,vector<vector<int>> &finalkey){
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


    vector<vector<int>> Decrypt(vector<vector<int>> &user_input,vector<vector<int>> &finalkey){
        // LOOK AT BELOW CODE ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR ERROR IT IS BASICALLY PSUEDO CODE BECAUSE I DONT KNOW HOW YOUR FUNCTIONS ARE STRUCTURED
        // I looked dude...there was very little actual errors, just edits need due to the change between using arrays and vectors.
        vector<vector<int>> newkey = KeyExpand(finalkey);

        // Round 10 does not do the mix columns step as it is the final round
        AddRoundKey(&user_input, &newkey , 40);
        // cout << "After Round "<<10<<" Inv Add round Key" << endl;
        // DebugDisplay(user_input);
        InvShiftRows(user_input);
        // cout << "After Round "<<10<<" Inv Shift Row" << endl;
        // DebugDisplay(user_input);
        InvUseSubBytes(user_input);
        // cout << "After Round "<<10<<" Inv Sub Bytes" << endl;
        // DebugDisplay(user_input);

        //Round 9-1
        for(int i = 9; i > 0; i--){
            AddRoundKey(&user_input, &newkey ,(i * 4));
            // cout << "After Round "<<i<<" Inv Add round Key" << endl;
            // DebugDisplay(user_input);
            InvMixColumns(user_input);
            // cout << "After Round "<<i<<" Inv Mix Columns" << endl;
            // DebugDisplay(user_input);
            InvShiftRows(user_input);
            // cout << "After Round "<<i<<" Inv Shift Rows" << endl;
            // DebugDisplay(user_input);
            InvUseSubBytes(user_input);
            // cout << "After Round "<<i<<" Inv Sub Bytes" << endl;
            // DebugDisplay(user_input);
        }


        //Round 0
        AddRoundKey(&user_input, &newkey, 0);
        // cout << "After Round "<<0<<" Inv Add round Key" << endl;
        // DebugDisplay(user_input);

        return user_input;
    };

    public:
        static vector<vector<int>> KeyGenerate() {
            vector<vector<int>> tempkey(4, vector<int> (4));

            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 4; y++) {
                    // (a << 4) | b equal ab in binary
                    tempkey[x][y] += ((rand() % 16) << 4) | (rand() % 16);
                }
            }

            return tempkey;
        };
        string EncryptMain(string &input_string, vector<vector<int>> key)
        {
            vector<vector<int>> data = FourByFour(input_string);

            data = Encrypt(data, key);

            string ret_str = "";
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                   ret_str += data[y][x];
                }
            }

            return ret_str;
        };
        string DecryptMain(string &input_string, vector<vector<int>> key)
        {
            vector<vector<int>> data = FourByFour(input_string);

            data = Decrypt(data, key);

            string ret_str = "";
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 4; x++) {
                   ret_str += data[y][x];
                }
            }

            return ret_str;
        };

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


vector<string> do_AES_encrypt(string orig_text, vector<vector<int>> key)
{
    int counter = 0;

    AES aes_obj;
    string temp_orig_text;
    string encrypted_text = "";
    string decrypted_text = "";


    int loops = orig_text.length() / 16;
    if(orig_text.length() % 16 != 0){
        loops += 1;
    }

    for(int i = 0; i < loops; i++){
        string temp_orig_text = "";

            for(int j = (i * 16); j < (i * 16 + 16); j++) {
                if (orig_text[j] == '\0') {
                    temp_orig_text += ' ';
                } else {
                    temp_orig_text += orig_text[j];
                }

            }
            encrypted_text += aes_obj.EncryptMain(temp_orig_text, key);
        }

    string key_str = "";
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            key_str += key[y][x];
        }
    }

    vector<string> ret = {key_str, encrypted_text, decrypted_text};
    return ret;
};


int main() {
    srand((unsigned int) time(NULL));
    string key_str, encrypted_text, decrypted_text;

    cout << "Choose which type of encryption would you like to see.\n 1. Caesar Cipher \n 2. Vigenere Cipher\n 3. Rijndael/AES\n";
    int choice;

    cin >> choice;

    string orig_text;
    ifstream myfile;
    myfile.open("input.txt");
    while (getline(myfile, orig_text));


    switch (choice) {

        case 1: {
            Ceaser ccode;
            ofstream my_file;

            ccode.Encrypt(orig_text);

            ccode.Decrypt(ccode.encoded_string, ccode.shift_value);

            break;
        }

        case 2: {
            ofstream my_file;
            Vigenere vcode;
            string vkey = "";

            vkey = vcode.KeyGenerate(orig_text);


            my_file.open("Key.txt", ios::out);
            my_file << vkey;
            my_file.close();

            my_file.open("Encrypted.txt", ios::out);
            my_file << vcode.Encrypt(orig_text, vkey);
            my_file.close();


            my_file.open("Decrypt.txt", ios::out);
            my_file << vcode.Decrypt(vcode.Encrypt(orig_text, vkey), vkey);;
            my_file.close();


            break;
        }

        case 3: {
            vector<vector<int>> key = AES::KeyGenerate();
            vector<string> ret_vals = do_AES_encrypt(orig_text, key);
            key_str = ret_vals[0];
            encrypted_text = ret_vals[1];
            decrypted_text = ret_vals[2];
            break;
        }

            ofstream my_file;
            my_file.open("Key.txt", ios::out);
            my_file << key_str;
            my_file.close();

            my_file.open("Encrypted.txt", ios::out);
            my_file << encrypted_text;
            my_file.close();

            my_file.open("Decrypt.txt", ios::out);
            my_file << decrypted_text;
            my_file.close();

            return 0;
    }
};
