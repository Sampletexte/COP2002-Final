#pragma once

#ifndef AES_H
#define AES_H


class AES
{
    private:
        static std::vector<std::vector<int>> invs_sbox, sbox;
        static const int Rcon[10];
        
        std::vector<int> CreateWi(std::vector<std::vector<int>> finalkey, int idx);
        void InvUseSubBytes(std::vector<std::vector<int>> &user_input);
        void AddRoundKey(std::vector<std::vector<int>> *user_input ,std::vector<std::vector<int>>  *new_key, int start);
        std::vector<int> MakeSubBytes(std::vector<int> user_input);
        std::vector<int> XorWi(std::vector<int> source, std::vector<int> second);
        std::vector<int> InvRotWord(std::vector<int> word);
        std::vector<std::vector<int>> KeyExpand(std::vector<std::vector<int>> finalkey);
        void InvShiftRows(std::vector<std::vector<int>> &user_input);
        int GladiousMul(int a, int b);
        void InvMixColumns(std::vector<std::vector<int>> &user_input);

        void KeyGenerate(std::vector<std::vector<int>> finalkey);
        std::vector<int> RotWord(std::vector<int> word);
        void UseSubBytes(std::vector<std::vector<int>> &user_input);
        std::vector<std::vector<int>> FourByFour(std::string orig_text);
        void ShiftRows(std::vector<std::vector<int>> &user_input);
        void MixColumns(std::vector<std::vector<int>> &user_input);

    public:
        std::vector<std::vector<int>> Decrypt(std::vector<std::vector<int>> &user_input,std::vector<std::vector<int>> &finalkey);
        std::vector<std::vector<int>> Encrypt(std::vector<std::vector<int>> &user_input,std::vector<std::vector<int>> &finalkey);
};



#endif