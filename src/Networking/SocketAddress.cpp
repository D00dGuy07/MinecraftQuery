#include "SocketAddress.h"

#include <ws2tcpip.h>

SocketAddress::SocketAddress(std::string address, std::string port)
{
    int result;
    addrinfo* result_list = NULL;
    addrinfo hints = {};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_DGRAM; // without this flag, getaddrinfo will return 3x the number of addresses (one for each socket type).
    result = getaddrinfo(address.c_str(), port.c_str(), &hints, &result_list);
    if (result == 0)
    {
        //ASSERT(result_list->ai_addrlen <= sizeof(sockaddr_in));
        memcpy(&Address, result_list->ai_addr, result_list->ai_addrlen);
        freeaddrinfo(result_list);
    }
}