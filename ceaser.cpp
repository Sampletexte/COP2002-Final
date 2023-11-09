// Include statements here
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

class Ceaser
{
    public:
        Ceaser(){};
        static vector<string> Encrypt(string input_text)
        {
            srand((unsigned int) time(NULL));

            int shift_value;
            while(1)
            {
                shift_value = 1 + rand()%26;
                if(shift_value != 26)
                    break;
            };

            string encoded_string = "";
            for(int i=0; i < input_text.length(); i++)
            {
                char letter = tolower(input_text[i]);
                if(letter >= 'a' && 'z' >= letter) {
                    char shifted_letter = letter + shift_value;



                    // Wrap the letter between a and z
                    int offset = mod(shifted_letter - 'a', 26);
                    if(offset < 0 || offset >  26 )
                    {
                        cout << "...";
                    };
                    encoded_string += offset + 'a';
                } else {
                    encoded_string += input_text[i];
                };
            };

            vector<string> ret_arr = {encoded_string, to_string(shift_value)};
            return ret_arr;
        };

        string Decrypt(string input_text, string key)
        {
            int shift_value = stoi(key);

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

        static void open_file(string filename, string *string_object)
        {
            ifstream File(filename);
            getline(File, *string_object);
            File.close();
        };

        static void save_file(string filename, string *string_object)
        {
            ofstream new_file(filename);
            new_file << *string_object;
            new_file.close();
        };


};


int main()
{
    Ceaser obj = Ceaser();
    string a;
    cout << "Enter: ";
    getline(cin, a);

    vector<string> ret = Ceaser::Encrypt(a);
    cout << "Key: " << ret[1] << endl << " Encryted: " << ret[0] << endl;
};