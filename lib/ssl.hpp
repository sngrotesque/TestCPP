#ifndef LIBSSL
#define LIBSSL
#include "network.hpp"
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/sslerr.h>
#include <openssl/crypto.h>

void ssl_test(std::string addr, const uint16_t port, std::string headers);

#endif
