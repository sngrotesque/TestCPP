#ifndef NETWORK
#define NETWORK
#include "baselib.hpp"
#include <Ws2tcpip.h>

void network_excetion(std::string funcName);

class Socket {
    private:
        ADDRINFO *getSockAddrInfo(const char *addr, const uint16_t port);

    public:
        SOCKET sockfd;
        int socket_family;
        int socket_type;
        int socket_proto;
        socklen_t transmissionLength;

        Socket(int _family, int _type, int _proto, SOCKET _fd = SOCKET_ERROR)
        : sockfd(), socket_family(_family), socket_type(_type), socket_proto(_proto)
        {
            if(_fd == SOCKET_ERROR) {
                this->sockfd = socket(this->socket_family, this->socket_type, this->socket_proto);
                if(this->sockfd == SOCKET_ERROR) {
                    network_excetion("Socket::Socket");
                }
            } else {
                this->sockfd = _fd;
            }
        }

        ~Socket() {}

        void bind(std::string addr, const uint16_t port);
        void listen(int backlog = 3);
        Socket *accept();
        void connect(std::string addr, const uint16_t port);
        void send(std::string buf, int flags = 0);
        void sendall(std::string buf, int flags = 0);
        std::string recv(uint32_t len, int flags = 0);
        void shutdown(int how);
        void close();
};

#endif
