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
//     Network/Win/UDPSocket.cpp : UDPSocket management for Windows           //
////////////////////////////////////////////////////////////////////////////////
#include "UDPSocket.h"


////////////////////////////////////////////////////////////////////////////////
//  UDPSocket default constructor                                             //
////////////////////////////////////////////////////////////////////////////////
UDPSocket::UDPSocket() :
m_handle(UDPSocketInvalid),
m_ipversion(UDPSOCKET_NONE)
{

}

////////////////////////////////////////////////////////////////////////////////
//  UDPSocket destructor                                                      //
////////////////////////////////////////////////////////////////////////////////
UDPSocket::~UDPSocket()
{
    closeSocket();
}


////////////////////////////////////////////////////////////////////////////////
//  Create UDP Socket                                                         //
////////////////////////////////////////////////////////////////////////////////
bool UDPSocket::createSocket(UDPSocketIPVersion ipversion, bool blocking)
{
    // Close current socket
    closeSocket();

    // Check IP version
    int addrfamily = AF_INET;
    if (ipversion == UDPSOCKET_IPV4)
    {
        // IPv4
        m_ipversion = UDPSOCKET_IPV4;
        addrfamily = AF_INET;
    }
    else if (ipversion == UDPSOCKET_IPV6)
    {
        // IPv6
        m_ipversion = UDPSOCKET_IPV6;
        addrfamily = AF_INET6;
    }
    else
    {
        // Invalid IP version
        return false;
    }

    // Create socket
    m_handle = socket(addrfamily, SOCK_DGRAM, IPPROTO_UDP);
    if (m_handle == UDPSocketInvalid)
    {
        // Unable to create socket
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

    // UDP Socket successfully created
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Close UDP Socket                                                          //
////////////////////////////////////////////////////////////////////////////////
void UDPSocket::closeSocket()
{
    if (m_handle != UDPSocketInvalid)
    {
        close(m_handle);
    }
    m_handle = UDPSocketInvalid;
    m_ipversion = UDPSOCKET_NONE;
}


////////////////////////////////////////////////////////////////////////////////
//  Bind UDP Socket                                                           //
////////////////////////////////////////////////////////////////////////////////
bool UDPSocket::bindSocket(uint16_t port)
{
    // Check socket handle
    if (m_handle == UDPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion == UDPSOCKET_IPV4)
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

        // UDP Socket successfully bound
        return true;
    }
    else if (m_ipversion == UDPSOCKET_IPV6)
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

        // UDP Socket successfully bound
        return true;
    }

    // Could not bind UDP Socket
    return false;
}


////////////////////////////////////////////////////////////////////////////////
//  Send data over UDP (IPv4)                                                 //
////////////////////////////////////////////////////////////////////////////////
bool UDPSocket::sendData(const char* data, size_t size,
    IPAddress4& ipaddress, uint16_t port)
{
    // Check socket handle
    if (m_handle == UDPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != UDPSOCKET_IPV4)
    {
        // Invalid IP version
        return false;
    }

    // Check data
    if (!data || (size <= 0))
    {
        // Invalid data
        return false;
    }

    // Remote address
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

    // Send data
    size_t dataSent = 0;
    int result = 0;
    do
    {
        result = sendto(
            m_handle, &data[dataSent],
            static_cast<int>(sizeof(char)*(size-dataSent)),
            0, (sockaddr*)&addr4, sizeof(addr4)
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
//  Send data over UDP (IPv6)                                                 //
////////////////////////////////////////////////////////////////////////////////
bool UDPSocket::sendData(const char* data, size_t size,
    IPAddress6& ipaddress, uint16_t port)
{
    // Check socket handle
    if (m_handle == UDPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != UDPSOCKET_IPV6)
    {
        // Invalid IP version
        return false;
    }

    // Check data
    if (!data || (size <= 0))
    {
        // Invalid data
        return false;
    }

    // Remote address
    sockaddr_in6 addr6;
    addr6.sin6_family = AF_INET6;
    addr6.sin6_port = htons(port);
    addr6.sin6_flowinfo = 0;
    addr6.sin6_addr = ipaddress.getAddress();
    addr6.sin6_scope_id = 0;

    // Send data
    size_t dataSent = 0;
    int result = 0;
    do
    {
        result = sendto(
            m_handle, &data[dataSent],
            static_cast<int>(sizeof(char)*(size-dataSent)),
            0, (sockaddr*)&addr6, sizeof(addr6)
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
//  Receive data over UDP (IPv4)                                              //
////////////////////////////////////////////////////////////////////////////////
bool UDPSocket::receiveData(char* data, size_t size,
    IPAddress4& ipaddress, uint16_t port)
{
    // Check socket handle
    if (m_handle == UDPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != UDPSOCKET_IPV4)
    {
        // Invalid IP version
        return false;
    }

    // Check data
    if (!data || (size <= 0))
    {
        // Invalid data
        return false;
    }

    // Remote address
    sockaddr_in addr4;
    addr4.sin_family = AF_INET6;
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
    socklen_t addr4Size = sizeof(addr4);

    // Receive data
    size_t dataReceived = 0;
    int result = 0;
    do
    {
        result = recvfrom(
            m_handle, &data[dataReceived],
            static_cast<int>(sizeof(char)*(size-dataReceived)),
            0, (sockaddr*)&addr4, &addr4Size
        );
        if (result <= 0)
        {
            // Unable to receive data
            return false;
        }
        dataReceived += static_cast<size_t>(result);
    } while (dataReceived < size);

    // Copy remote IP address
    ipaddress.setAddress(addr4.sin_addr);

    // Data successfully received
    return true;
}

////////////////////////////////////////////////////////////////////////////////
//  Receive data over UDP (IPv6)                                              //
////////////////////////////////////////////////////////////////////////////////
bool UDPSocket::receiveData(char* data, size_t size,
    IPAddress6& ipaddress, uint16_t port)
{
    // Check socket handle
    if (m_handle == UDPSocketInvalid)
    {
        // Invalid socket handle
        return false;
    }

    // Check IP version
    if (m_ipversion != UDPSOCKET_IPV6)
    {
        // Invalid IP version
        return false;
    }

    // Check data
    if (!data || (size <= 0))
    {
        // Invalid data
        return false;
    }

    // Remote address
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
    socklen_t addr6Size = sizeof(addr6);

    // Receive data
    size_t dataReceived = 0;
    int result = 0;
    do
    {
        result = recvfrom(
            m_handle, &data[dataReceived],
            static_cast<int>(sizeof(char)*(size-dataReceived)),
            0, (sockaddr*)&addr6, &addr6Size
        );
        if (result <= 0)
        {
            // Unable to receive data
            return false;
        }
        dataReceived += static_cast<size_t>(result);
    } while (dataReceived < size);

    // Copy remote IP address
    ipaddress.setAddress(addr6.sin6_addr);

    // Data successfully received
    return true;
}
