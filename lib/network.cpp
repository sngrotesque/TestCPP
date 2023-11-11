#include "network.hpp"

ADDRINFO *Socket::getSockAddrInfo(const char *addr, const uint16_t port)
{
    ADDRINFO hints, *result = nullptr;
    memset(&hints, 0x00, sizeof(hints));
    hints.ai_family = this->socket_family;
    hints.ai_socktype = this->socket_type;
    hints.ai_protocol = this->socket_proto;
    if(getaddrinfo(addr, std::to_string(port).c_str(), &hints, &result)) {
        network_excetion("Socket::getSockAddrInfo");
    }
    return result;
}

void network_excetion(std::string funcName)
{
    throw std::runtime_error(funcName + " error code: " + std::to_string(WSAGetLastError()) + ".");
}

void Socket::bind(std::string addr, const uint16_t port)
{
    ADDRINFO *AddrInfo = getSockAddrInfo(addr.c_str(), port);
    int err = ::bind(this->sockfd, AddrInfo->ai_addr, AddrInfo->ai_addrlen);
    if(err == SOCKET_ERROR) {
        network_excetion("Socket::bind");
    }
    freeaddrinfo(AddrInfo);
}

void Socket::listen(int backlog)
{
    int err = ::listen(this->sockfd, backlog);
    if(err == SOCKET_ERROR) {
        network_excetion("Socket::listen");
    }
}

Socket *Socket::accept()
{
    SOCKADDR client_addr;
    socklen_t client_addrlen = sizeof(client_addr);
    SOCKET client_sockfd = ::accept(this->sockfd, &client_addr, &client_addrlen);
    if(client_sockfd == SOCKET_ERROR) {
        network_excetion("Socket::accept");
    }
    return new Socket(this->socket_family, this->socket_type, this->socket_proto, client_sockfd);
}

void Socket::connect(std::string addr, const uint16_t port)
{
    ADDRINFO *AddrInfo = this->getSockAddrInfo(addr.c_str(), port);
    int err = ::connect(this->sockfd, AddrInfo->ai_addr, AddrInfo->ai_addrlen);
    if(err == SOCKET_ERROR) {
        network_excetion("Socket::connect");
    }
    freeaddrinfo(AddrInfo);
}

void Socket::send(std::string buf, int flags)
{
    this->transmissionLength = ::send(this->sockfd, buf.c_str(), buf.size(), flags);
    if(this->transmissionLength == EOF) {
        network_excetion("Socket::send");
    }
}

void Socket::sendall(std::string buf, int flags)
{
    char *offset_ptr = (char *)buf.c_str();
    uint32_t size = (socklen_t)buf.size();
    uint32_t retry_count = 5;

    while(size) {
        this->transmissionLength = ::send(this->sockfd, offset_ptr, size, flags);
        if(this->transmissionLength == SOCKET_ERROR && retry_count--) {
            continue;
        }
        offset_ptr += this->transmissionLength;
        size -= this->transmissionLength;
    }
}

std::string Socket::recv(uint32_t len, int flags)
{
    char *_tmp = (char *)malloc(len);
    this->transmissionLength = ::recv(this->sockfd, _tmp, len, flags);
    if(this->transmissionLength == SOCKET_ERROR) {
        network_excetion("Socket::recv");
    }
    std::string content(_tmp, this->transmissionLength);
    free(_tmp);
    return content;
}

void Socket::shutdown(int how)
{
    int err = ::shutdown(this->sockfd, how);
    if(err == SOCKET_ERROR) {
        network_excetion("Socket::shutdown");
    }
}

void Socket::close()
{
    int err = closesocket(this->sockfd);
    if(err == SOCKET_ERROR) {
        network_excetion("Socket::close");
    }
}
