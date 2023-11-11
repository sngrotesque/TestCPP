#include "ssl.hpp"

void ssl_disable(SSL_CTX *ctx)
{
    uint64_t options = SSL_OP_NO_SSLv2 | SSL_OP_NO_SSLv3;
    options |= (SSL_OP_NO_TLSv1 | SSL_OP_NO_TLSv1_1);
    options |= (SSL_OP_CIPHER_SERVER_PREFERENCE | SSL_OP_NO_RENEGOTIATION);
    SSL_CTX_set_options(ctx, options);
    SSL_CTX_set_cipher_list(ctx, "HIGH:!aNULL:!eNULL");
}

void ssl_test(std::string addr, const uint16_t port, std::string headers)
{
    SSL_CTX *ssl_ctx = nullptr;
    SSL *ssl = nullptr;
    Socket *sockfd = nullptr;
    char recvbuf[4096] = {0};

    ssl_ctx = SSL_CTX_new(TLS_method());
    ssl_disable(ssl_ctx);
    ssl = SSL_new(ssl_ctx);
    sockfd = new Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    SSL_set_fd(ssl, sockfd->sockfd);
    SSL_set_tlsext_host_name(ssl, addr.c_str());

    sockfd->connect(addr, port);
    SSL_connect(ssl);

    SSL_write(ssl, headers.c_str(), headers.size());
    SSL_read(ssl, recvbuf, sizeof(recvbuf));

    std::cout << recvbuf << std::endl;

    sockfd->shutdown(SD_BOTH);
    sockfd->close();
    delete sockfd;
    SSL_CTX_free(ssl_ctx);
    SSL_free(ssl);
}
