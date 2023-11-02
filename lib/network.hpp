#ifndef NETWORK
#define NETWORK
#include "baselib.hpp"
#include <Ws2tcpip.h>

bool WSAData_Enable = false;

class Socket {
    private:
        SOCKET sockfd;
        ADDRINFO *SockAddrResult;
        ADDRINFO hints;

        int socket_family;
        int socket_type;
        int socket_proto;

    public:
        Socket(int _family, int _type, int _proto, SOCKET _fd = EOF)
        : sockfd(), SockAddrResult(), hints(),
        socket_family(_family), socket_type(_type), socket_proto(_proto)
        {
            if(!WSAData_Enable) {
                WSAData_Enable = true;
                WSADATA ws;
                if(WSAStartup(MAKEWORD(2,2), &ws)) {
                    std::string code = std::to_string(WSAGetLastError());
                    throw std::runtime_error("error code: " + code + ".");
                }
            }
            if(_fd == EOF) {
                this->sockfd = socket(this->socket_family, this->socket_type, this->socket_proto);
            } else {
                this->sockfd = _fd;
            }

            hints.ai_family = this->socket_family;
        }

        ~Socket()
        {
            if(WSAData_Enable) {
                WSACleanup();
            }
        }
};

#endif
