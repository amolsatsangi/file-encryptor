#pragma once
#include<vector>
#include<cstdint>

class CryptoEngine{
    public:
        virtual ~CryptoEngine()=default;
        virtual std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plainText)=0;
        virtual std::vector<uint8_t> decrypt(const std::vector<uint8_t> &cipherText)=0;
};