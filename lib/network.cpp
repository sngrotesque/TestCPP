#include "network.hpp"

void network_excetion()
{
    throw std::runtime_error("error code: " + std::to_string(WSAGetLastError()) + ".");
}

void Socket::bind(std::string addr, uint16_t port)
{
    
}   


