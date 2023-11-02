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
                int err = WSAStartup(MAKEWORD(2,2), &ws);
                if(err == SOCKET_ERROR) {
                    throw std::runtime_error("");
                }
            }
            if(_fd == EOF) {
                this->sockfd = socket(socket_family, socket_type, socket_proto);
            } else {
                this->sockfd = _fd;
            }
        }
};

#endif
