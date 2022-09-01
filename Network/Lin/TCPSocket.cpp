////////////////////////////////////////////////////////////////////////////////
//     _______                       ____________________________________     //
//     \\ .   \            _________/ . . . . . . . . . . . . . . . .   /     //
//      \\ .   \       ___/ . . . . .    ______________________________/      //
//       \\ .   \   __/. . .   _________/     /    // .  __________/          //
//        \\ .   \_//      ___/ .  _____     /    // .  /______               //
//         \\ .   \/     _/ // .  /    \\    |    \\  .        \              //
//          \\ .        /   || .  |    ||    |     \\______     \             //
//           \\ .      /    || .  \____//    |  _________//     /             //
//            \\ .    /     //  .            / // . . . .      /              //
//             \\____/     //_______________/ //______________/               //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////
//   This is free and unencumbered software released into the public domain.  //
//                                                                            //
//   Anyone is free to copy, modify, publish, use, compile, sell, or          //
//   distribute this software, either in source code form or as a compiled    //
//   binary, for any purpose, commercial or non-commercial, and by any        //
//   means.                                                                   //
//                                                                            //
//   In jurisdictions that recognize copyright laws, the author or authors    //
//   of this software dedicate any and all copyright interest in the          //
//   software to the public domain. We make this dedication for the benefit   //
//   of the public at large and to the detriment of our heirs and             //
//   successors. We intend this dedication to be an overt act of              //
//   relinquishment in perpetuity of all present and future rights to this    //
//   software under copyright law.                                            //
//                                                                            //
//   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,          //
//   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF       //
//   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.   //
//   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR        //
//   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,    //
//   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR    //
//   OTHER DEALINGS IN THE SOFTWARE.                                          //
//                                                                            //
//   For more information, please refer to <https://unlicense.org>            //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Network/Lin/TCPSocket.cpp : TCPSocket management for Linux             //
////////////////////////////////////////////////////////////////////////////////
#include "TCPSocket.h"


////////////////////////////////////////////////////////////////////////////////
//  TCPSocket default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
TCPSocket::TCPSocket() :
m_handle(TCPSocketInvalid),
m_ipversion(TCPSOCKET_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  TCPSocket destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
TCPSocket::~TCPSocket()
{
    closeSocket();
}


////////////////////////////////////////////////////////////////////////////////
//  Create TCP Socket                                                         //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::createSocket(TCPSocketIPVersion ipversion, bool blocking)
{
    // Close current socket
    closeSocket();

    // Check IP version
    int addrfamily = AF_INET;
    if (ipversion == TCPSOCKET_IPV4)
    {
        // IPv4
        m_ipversion = TCPSOCKET_IPV4;
        addrfamily = AF_INET;
    }
    else if (ipversion == TCPSOCKET_IPV6)
    {
        // IPv6
        m_ipversion = TCPSOCKET_IPV6;
        addrfamily = AF_INET6;
    }
    else
    {
        // Invalid IP version
        return false;
    }

    // Create socket
    m_handle = socket(addrfamily, SOCK_STREAM, IPPROTO_TCP);
    if (m_handle == TCPSocketInvalid)
    {
        // Unable to create socket
        return false;
    }

    // Disable TCP packets buffering
    uint32_t optval = 1;
    if (setsockopt(m_handle, IPPROTO_TCP, TCP_NODELAY,
        (char*)&optval, sizeof(optval)) != 0)
    {
        // Could not disable TCP packets buffering
        return false;
    }

    // Set socket blocking state
    int statusFlags = fcntl(m_handle, F_GETFL);
    if (blocking) { statusFlags &= ~O_NONBLOCK; }
    else { statusFlags |= O_NONBLOCK; }
    if (fcntl(m_handle, F_SETFL, statusFlags) != 0)
    {
        // Could not set socket blocking state
        return false;
    }

    // TCP Socket successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Close TCP Socket                                                          //
////////////////////////////////////////////////////////////////////////////////
void TCPSocket::closeSocket()
{
    if (m_handle != TCPSocketInvalid)
    {
        close(m_handle);
    }
    m_handle = TCPSocketInvalid;
    m_ipversion = TCPSOCKET_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind TCP Socket                                                           //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::bindSocket(uint16_t port)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion == TCPSOCKET_IPV4)
    {
        // IPv4
        sockaddr_in addr4;
        addr4.sin_family = AF_INET;
        addr4.sin_port = htons(port);
        addr4.sin_addr.s_addr = 0;
        addr4.sin_zero[0] = 0;
        addr4.sin_zero[1] = 0;
        addr4.sin_zero[2] = 0;
        addr4.sin_zero[3] = 0;
        addr4.sin_zero[4] = 0;
        addr4.sin_zero[5] = 0;
        addr4.sin_zero[6] = 0;
        addr4.sin_zero[7] = 0;

        // Bind socket
        if (bind(m_handle, (sockaddr*)&addr4, sizeof(addr4)) != 0)
        {
            // Could not bind socket
            return false;
        }

        // TCP Socket successfully bound
        return true;
    }
    else if (m_ipversion == TCPSOCKET_IPV6)
    {
        // IPv6
        sockaddr_in6 addr6;
        addr6.sin6_family = AF_INET6;
        addr6.sin6_port = htons(port);
        addr6.sin6_flowinfo = 0;
        addr6.sin6_addr.s6_addr16[0] = 0;
        addr6.sin6_addr.s6_addr16[1] = 0;
        addr6.sin6_addr.s6_addr16[2] = 0;
        addr6.sin6_addr.s6_addr16[3] = 0;
        addr6.sin6_addr.s6_addr16[4] = 0;
        addr6.sin6_addr.s6_addr16[5] = 0;
        addr6.sin6_addr.s6_addr16[6] = 0;
        addr6.sin6_addr.s6_addr16[7] = 0;
        addr6.sin6_scope_id = 0;

        // Bind socket
        if (bind(m_handle, (sockaddr*)&addr6, sizeof(addr6)) != 0)
        {
            // Could not bind socket
            return false;
        }

        // TCP Socket successfully bound
        return true;
    }

    // Could not bind TCP Socket
    return false;
}

////////////////////////////////////////////////////////////////////////////////
//  Listen bound port                                                         //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::listenPort()
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Listen bound port
    if (listen(m_handle, TCPSocketMaxBackLog) != 0)
    {
        // Unable to listen bound port
        return false;
    }

    // TCP Socket is listening bound port
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Accept incoming connection (IPv4)                                         //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::acceptConnection(TCPSocket& socket, IPAddress4& ipaddress)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != TCPSOCKET_IPV4)
    {
        // Invalid IP version
        return false;
    }

    // Close current socket
    socket.closeSocket();

    // Incoming connection address
    sockaddr_in addr4;
    addr4.sin_family = 0;
    addr4.sin_port = 0;
    addr4.sin_addr.s_addr = 0;
    addr4.sin_zero[0] = 0;
    addr4.sin_zero[1] = 0;
    addr4.sin_zero[2] = 0;
    addr4.sin_zero[3] = 0;
    addr4.sin_zero[4] = 0;
    addr4.sin_zero[5] = 0;
    addr4.sin_zero[6] = 0;
    addr4.sin_zero[7] = 0;
    socklen_t addr4Size = sizeof(addr4);

    // Accept incoming connection
    socket.m_handle = accept(m_handle, (sockaddr*)&addr4, &addr4Size);
    if (socket.m_handle == TCPSocketInvalid)
    {
        // Unable to accept incoming connection
        return false;
    }

    // Copy incoming connection IP address
    ipaddress.setAddress(addr4.sin_addr);

    // Incoming connection successfully accepted
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Accept incoming connection (IPv6)                                         //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::acceptConnection(TCPSocket& socket, IPAddress6& ipaddress)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != TCPSOCKET_IPV6)
    {
        // Invalid IP version
        return false;
    }

    // Close current socket
    socket.closeSocket();

    // Incoming connection address
    sockaddr_in6 addr6;
    addr6.sin6_family = 0;
    addr6.sin6_port = 0;
    addr6.sin6_flowinfo = 0;
    addr6.sin6_addr.s6_addr16[0] = 0;
    addr6.sin6_addr.s6_addr16[1] = 0;
    addr6.sin6_addr.s6_addr16[2] = 0;
    addr6.sin6_addr.s6_addr16[3] = 0;
    addr6.sin6_addr.s6_addr16[4] = 0;
    addr6.sin6_addr.s6_addr16[5] = 0;
    addr6.sin6_addr.s6_addr16[6] = 0;
    addr6.sin6_addr.s6_addr16[7] = 0;
    addr6.sin6_scope_id = 0;
    socklen_t addr6Size = sizeof(addr6);

    // Accept incoming connection
    socket.m_handle = accept(m_handle, (sockaddr*)&addr6, &addr6Size);
    if (socket.m_handle == TCPSocketInvalid)
    {
        // Unable to accept incoming connection
        return false;
    }

    // Copy incoming connection IP address
    ipaddress.setAddress(addr6.sin6_addr);

    // Incoming connection successfully accepted
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Connect TCP socket to IP address (IPv4)                                   //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::connectSocket(IPAddress4& ipaddress, uint16_t port)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != TCPSOCKET_IPV4)
    {
        // Invalid IP version
        return false;
    }

    // Host address
    sockaddr_in addr4;
    addr4.sin_family = AF_INET;
    addr4.sin_port = htons(port);
    addr4.sin_addr = ipaddress.getAddress();
    addr4.sin_zero[0] = 0;
    addr4.sin_zero[1] = 0;
    addr4.sin_zero[2] = 0;
    addr4.sin_zero[3] = 0;
    addr4.sin_zero[4] = 0;
    addr4.sin_zero[5] = 0;
    addr4.sin_zero[6] = 0;
    addr4.sin_zero[7] = 0;

    // Connect socket
    if (connect(m_handle, (sockaddr*)&addr4, sizeof(addr4)) != 0)
    {
        return false;
    }

    // TCP Socket successfully connected
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Connect TCP socket to IP address (IPv6)                                   //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::connectSocket(IPAddress6& ipaddress, uint16_t port)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != TCPSOCKET_IPV6)
    {
        // Invalid IP version
        return false;
    }

    // Host address
    sockaddr_in6 addr6;
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port);
    addr6.sin6_flowinfo = 0;
    addr6.sin6_addr = ipaddress.getAddress();
    addr6.sin6_scope_id = 0;

    // Connect socket
    if (connect(m_handle, (sockaddr*)&addr6, sizeof(addr6)) != 0)
    {
        return false;
    }

    // TCP Socket successfully connected
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Send data over TCP                                                        //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::sendData(const char* data, size_t size)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check data
    if (!data || (size <= 0))
    {
        // Invalid data
        return false;
    }

    // Send data
    size_t dataSent = 0;
    int result = 0;
    do
    {
        result = send(
            m_handle, &data[dataSent],
            static_cast<int>(sizeof(char)*(size-dataSent)),
            0
        );
        if (result < 0)
        {
            // Unable to send data
            return false;
        }
        dataSent += static_cast<size_t>(result);
    } while (dataSent < size);

    // Data successfully sent
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Receive data over TCP                                                     //
////////////////////////////////////////////////////////////////////////////////
bool TCPSocket::receiveData(char* data, size_t size)
{
    // Check socket handle
    if (m_handle == TCPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check data
    if (!data || (size <= 0))
    {
        // Invalid data
        return false;
    }

    // Receive data
    size_t dataReceived = 0;
    int result = 0;
    do
    {
        result = recv(
            m_handle, &data[dataReceived],
            static_cast<int>(sizeof(char)*(size-dataReceived)),
            0
        );
        if (result <= 0)
        {
            // Unable to receive data
            return false;
        }
        dataReceived += static_cast<size_t>(result);
    } while (dataReceived < size);

    // Data successfully received
    return true;
}
