#ifndef CRYPTO
#define CRYPTO
#include "baselib.hpp"

class Crypto {
    private:
        uint8_t key[32];

    public:
        Crypto(uint8_t *UserKey)
        {
            memcpy(this->key, UserKey, sizeof(this->key));
        }

        void encrypt(uint8_t *buf, size_t len);
        void decrypt(uint8_t *buf, size_t len);
};

#endif
