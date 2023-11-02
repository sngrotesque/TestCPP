#include "lib/baselib.hpp"
#include "lib/crypto.hpp"
#include "lib/network.hpp"

void start_service()
{
    WSADATA ws;
    if(WSAStartup(MAKEWORD(2,2), &ws)) {
        network_excetion("start_service");
    }
}

void stop_service()
{
    WSACleanup();
}

void networkFunctionRun(void (*func)())
{
    start_service();
    func();
    stop_service();
}

void network_class_test()
{
    Socket *sockfd = new Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::string addr = "47.243.162.23";
    const uint16_t port = 80;
    std::string userAgent = "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/114.0";

    std::string sendbuf = (
        "GET / HTTP/1.1\r\n"
        "Host: "+addr+"\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "User-Agent: " + userAgent + "\r\n\r\n"
    );
    std::string recvbuf;

    sockfd->connect(addr, port);
    sockfd->send(sendbuf);
    recvbuf = sockfd->recv(4096);
    sockfd->shutdown(SD_BOTH);
    sockfd->close();

    std::cout << recvbuf << std::endl;

    delete sockfd;
}

void crypto_class_test()
{
    const char *key = "sd813y59yasdnlSDO135l13[posa813]";
    char content[256] = {"hello, world.\n"};
    size_t content_len = strlen(content);
    Crypto *ctx = nullptr;

    ctx = new Crypto((uint8_t *)key);
    printHexArray((uint8_t *)content, content_len, 32, 1, 0);
    ctx->encrypt((uint8_t *)content, strlen(content));
    printHexArray((uint8_t *)content, content_len, 32, 1, 0);
    ctx->decrypt((uint8_t *)content, strlen(content));
    printHexArray((uint8_t *)content, content_len, 32, 1, 0);
    delete ctx;
}

int main(int argc, char **argv)
{
    crypto_class_test();

    return 0;
}
