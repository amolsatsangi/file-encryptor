#pragma once
#include "CryptoEngine.hpp"
#include <sodium.h>

class SodiumCryptoEngine : public CryptoEngine{
    public:
        SodiumCryptoEngine();
        virtual ~SodiumCryptoEngine()=default;
        std::vector<uint8_t> encrypt(const std::vector<uint8_t> &plainText) override;
        std::vector<uint8_t> decrypt(const std::vector<uint8_t> &cipherText) override;
    private:
        unsigned char key[crypto_secretbox_KEYBYTES];  //Key size = crypto_secretbox_KEYBYTES (32 bytes)
};