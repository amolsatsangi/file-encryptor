#include<vector>
#include "SodiumCryptoEngine.hpp"
#include <stdexcept>
#include<iostream>
SodiumCryptoEngine::SodiumCryptoEngine(){
    if (sodium_init() < 0) {
        throw std::runtime_error("libsodium initialization failed");
    }
    randombytes_buf(key, sizeof key);
}
std::vector<uint8_t> SodiumCryptoEngine::encrypt(const std::vector<uint8_t> &plainText) {
    std::vector<uint8_t> nonce(crypto_secretbox_NONCEBYTES); //crypto_secretbox_NONCEBYTES = 24 bytes = 192 bits
    randombytes_buf(nonce.data(), nonce.size());
    std::cout<<nonce.size()<<std::endl;
    std::vector<uint8_t> cipher(
        crypto_secretbox_MACBYTES + plainText.size()
    );

    crypto_secretbox_easy(cipher.data(),plainText.data(),plainText.size(),nonce.data(),key);

    // prepend nonce
    nonce.insert(nonce.end(), cipher.begin(), cipher.end());
    return nonce;
}

std::vector<uint8_t> SodiumCryptoEngine::decrypt(const std::vector<uint8_t>& cipherText) {
    if (cipherText.size() < crypto_secretbox_NONCEBYTES)
        throw std::runtime_error("Invalid ciphertext");

    const unsigned char* nonce = cipherText.data();
    const unsigned char* cipher = cipherText.data() + crypto_secretbox_NONCEBYTES;
    size_t cipher_len = cipherText.size() - crypto_secretbox_NONCEBYTES;

    std::vector<uint8_t> plain(
        cipher_len - crypto_secretbox_MACBYTES
    );

    if (crypto_secretbox_open_easy(plain.data(),cipher,cipher_len,nonce,key) != 0) {
        throw std::runtime_error("Decryption failed");
    }
    return plain;
}