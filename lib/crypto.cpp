#include "crypto.hpp"

void Crypto::encrypt(uint8_t *buf, size_t len)
{
    size_t index;
    for(index = 0; index < len; ++index) {
        buf[index] ^= this->key[index % sizeof(this->key)];
        buf[index] -= this->key[index % sizeof(this->key)];
        buf[index] ^= this->key[index % sizeof(this->key)];
        buf[index] += this->key[index % sizeof(this->key)];
    }
}

void Crypto::decrypt(uint8_t *buf, size_t len)
{
    size_t index;
    for(index = 0; index < len; ++index) {
        buf[index] -= this->key[index % sizeof(this->key)];
        buf[index] ^= this->key[index % sizeof(this->key)];
        buf[index] += this->key[index % sizeof(this->key)];
        buf[index] ^= this->key[index % sizeof(this->key)];
    }
}
