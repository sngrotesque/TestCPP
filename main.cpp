#include "lib/baselib.hpp"
#include "lib/crypto.hpp"
#include "lib/network.hpp"
#include "lib/file.hpp"
#include "lib/ssl.hpp"

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
    std::string addr = "passport.bilibili.com";
    std::string userAgent = "Mozilla/5.0 (X11; Linux x86_64; rv:109.0) Gecko/20100101 Firefox/114.0";
    std::string HTTP_Headers = (
        "GET /qrcode/getLoginUrl HTTP/1.1\r\n"
        "Host: "+addr+"\r\n"
        "Accept: */*\r\n"
        "Connection: close\r\n"
        "User-Agent: "+userAgent+"\r\n\r\n");

    start_service();
    ssl_test(addr, 443, HTTP_Headers);
    stop_service();

    return 0;
}
