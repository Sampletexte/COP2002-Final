//
// Created by nicho on 10/26/2023.
// snake_case for variables/filenames; CamelCase for func/class

#include <iostream>
#include <fstream>
#include <ctime>


using namespace std;

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

            char temp = (x[i] + key[i] -(2 * 'a') + 1) % 26;
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
                char temp = (y[i] - key[i] + 25) % 26;
                newtext.push_back(temp + 'a');
            }
        }return newtext;

    };
};

int main() {
    fstream my_file;
    Vigenere code;
    string user_input;
    string finalkey;
    string encrypted;
    string decrypted;


    srand((unsigned int) time(NULL));
    cout << "Please input your original text.";
    getline(cin, user_input);



    finalkey = code.KeyGenerate(user_input);

    my_file.open("../Vigenerekey.txt", ios::out);
    my_file << finalkey;
    my_file.close();



    encrypted = code.Encrypt(user_input, finalkey);

    my_file.open("../Vigenere.txt", ios::out);
    my_file << encrypted;
    my_file.close();



    decrypted = code.Decrypt(encrypted,finalkey);

    my_file.open("../Vigenere.decrypt.txt",ios::out);
    my_file << decrypted;
    my_file.close();

}

