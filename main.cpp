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

int main(int argc, char **argv)
{
    Socket *sockfd = new Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    std::string addr = "www.bilibili.com";
    const uint16_t port = 80;

    std::string sendbuf = (
        "GET / HTTP/1.1\r\n"
        "Host: "+addr+"\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "User-Agent: Android\r\n\r\n"
    );
    std::string recvbuf;

    sockfd->connect(addr, port);
    sockfd->send(sendbuf);
    sockfd->recv(4096);
    sockfd->shutdown(SD_BOTH);
    sockfd->close();

    std::cout << recvbuf << std::endl;

    delete sockfd;
    return 0;
}
