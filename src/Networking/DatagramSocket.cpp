#include "DatagramSocket.h"

#include <iostream>

DatagramSocket::DatagramSocket(uint32_t timeout)
{
    int result = 0;

    m_Socket = socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(m_Socket, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<char*>(&timeout), sizeof(DWORD));
    setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&timeout), sizeof(DWORD));

    m_ListenAddress.sin_family = AF_INET;
    result = bind(m_Socket, (sockaddr*)&m_ListenAddress, sizeof(m_ListenAddress));
}

DatagramSocket::~DatagramSocket()
{
    if (m_Socket)
        closesocket(m_Socket);
}

void DatagramSocket::Send(SocketAddress& address, void* data, int len)
{
    sendto(m_Socket, reinterpret_cast<char*>(data), len, 0, (sockaddr*)&(address.Address), sizeof(address.Address));
}

std::vector<char> DatagramSocket::Listen(SocketAddress& address, int bufferSize)
{
    std::vector<char> buffer = std::vector<char>(bufferSize);

    int fromlensize = sizeof(address.Address);
    recvfrom(m_Socket, buffer.data(), bufferSize, 0, (sockaddr*)&(address.Address), &fromlensize);

    return buffer;
}
