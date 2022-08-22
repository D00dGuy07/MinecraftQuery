/* 
MIT License

Copyright (c) 2022 D00dGuy07

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

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
