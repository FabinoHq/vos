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
//     Network/Lin/IPAddress6.cpp : IPv6 address management for Linux         //
////////////////////////////////////////////////////////////////////////////////
#include "IPAddress6.h"


////////////////////////////////////////////////////////////////////////////////
//  IPAddress6 default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
IPAddress6::IPAddress6() :
m_ipaddress()
{
    m_ipaddress.s6_addr16[0] = 0;
    m_ipaddress.s6_addr16[1] = 0;
    m_ipaddress.s6_addr16[2] = 0;
    m_ipaddress.s6_addr16[3] = 0;
    m_ipaddress.s6_addr16[4] = 0;
    m_ipaddress.s6_addr16[5] = 0;
    m_ipaddress.s6_addr16[6] = 0;
    m_ipaddress.s6_addr16[7] = 0;
}

////////////////////////////////////////////////////////////////////////////////
//  IPAddress6 copy constructor                                               //
////////////////////////////////////////////////////////////////////////////////
IPAddress6::IPAddress6(const IPAddress6& ipaddress) :
m_ipaddress()
{
    m_ipaddress.s6_addr16[0] = ipaddress.m_ipaddress.s6_addr16[0];
    m_ipaddress.s6_addr16[1] = ipaddress.m_ipaddress.s6_addr16[1];
    m_ipaddress.s6_addr16[2] = ipaddress.m_ipaddress.s6_addr16[2];
    m_ipaddress.s6_addr16[3] = ipaddress.m_ipaddress.s6_addr16[3];
    m_ipaddress.s6_addr16[4] = ipaddress.m_ipaddress.s6_addr16[4];
    m_ipaddress.s6_addr16[5] = ipaddress.m_ipaddress.s6_addr16[5];
    m_ipaddress.s6_addr16[6] = ipaddress.m_ipaddress.s6_addr16[6];
    m_ipaddress.s6_addr16[7] = ipaddress.m_ipaddress.s6_addr16[7];
}

////////////////////////////////////////////////////////////////////////////////
//  IPAddress6 destructor                                                     //
////////////////////////////////////////////////////////////////////////////////
IPAddress6::~IPAddress6()
{
    m_ipaddress.s6_addr16[0] = 0;
    m_ipaddress.s6_addr16[1] = 0;
    m_ipaddress.s6_addr16[2] = 0;
    m_ipaddress.s6_addr16[3] = 0;
    m_ipaddress.s6_addr16[4] = 0;
    m_ipaddress.s6_addr16[5] = 0;
    m_ipaddress.s6_addr16[6] = 0;
    m_ipaddress.s6_addr16[7] = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set IP address v6 representation                                          //
////////////////////////////////////////////////////////////////////////////////
void IPAddress6::setAddress(in6_addr ipaddress)
{
    m_ipaddress.s6_addr16[0] = ipaddress.s6_addr16[0];
    m_ipaddress.s6_addr16[1] = ipaddress.s6_addr16[1];
    m_ipaddress.s6_addr16[2] = ipaddress.s6_addr16[2];
    m_ipaddress.s6_addr16[3] = ipaddress.s6_addr16[3];
    m_ipaddress.s6_addr16[4] = ipaddress.s6_addr16[4];
    m_ipaddress.s6_addr16[5] = ipaddress.s6_addr16[5];
    m_ipaddress.s6_addr16[6] = ipaddress.s6_addr16[6];
    m_ipaddress.s6_addr16[7] = ipaddress.s6_addr16[7];
}


////////////////////////////////////////////////////////////////////////////////
//  Resolve host name into IP address                                         //
////////////////////////////////////////////////////////////////////////////////
bool IPAddress6::resolveHostName(const std::string& hostName)
{
    addrinfo hints;
    hints.ai_flags = 0;
    hints.ai_family = AF_INET6;
    hints.ai_socktype = 0;
    hints.ai_protocol = 0;
    hints.ai_addrlen = 0;
    hints.ai_canonname = 0;
    hints.ai_addr = 0;
    hints.ai_next = 0;

    // Resolve host name
    addrinfo* result = 0;
    if (getaddrinfo(hostName.c_str(), 0, &hints, &result) != 0)
    {
        // Could not resolve host name
        return false;
    }
    if (!result)
    {
        // Could not resolve host name
        return false;
    }

    // Get IP address
    sockaddr_in6 addr;
    addr.sin6_family = 0;
    addr.sin6_port = 0;
    addr.sin6_flowinfo = 0;
    addr.sin6_addr.s6_addr16[0] = 0;
    addr.sin6_addr.s6_addr16[1] = 0;
    addr.sin6_addr.s6_addr16[2] = 0;
    addr.sin6_addr.s6_addr16[3] = 0;
    addr.sin6_addr.s6_addr16[4] = 0;
    addr.sin6_addr.s6_addr16[5] = 0;
    addr.sin6_addr.s6_addr16[6] = 0;
    addr.sin6_addr.s6_addr16[7] = 0;
    addr.sin6_scope_id = 0;
    memcpy(&addr, result->ai_addr, sizeof(addr));
    freeaddrinfo(result);

    // Set IP address
    m_ipaddress.s6_addr16[0] = addr.sin6_addr.s6_addr16[0];
    m_ipaddress.s6_addr16[1] = addr.sin6_addr.s6_addr16[1];
    m_ipaddress.s6_addr16[2] = addr.sin6_addr.s6_addr16[2];
    m_ipaddress.s6_addr16[3] = addr.sin6_addr.s6_addr16[3];
    m_ipaddress.s6_addr16[4] = addr.sin6_addr.s6_addr16[4];
    m_ipaddress.s6_addr16[5] = addr.sin6_addr.s6_addr16[5];
    m_ipaddress.s6_addr16[6] = addr.sin6_addr.s6_addr16[6];
    m_ipaddress.s6_addr16[7] = addr.sin6_addr.s6_addr16[7];

    // Host name resolved
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Get IP address v6 string                                                  //
////////////////////////////////////////////////////////////////////////////////
std::string IPAddress6::getString() const
{
    char cstraddress[INET6_ADDRSTRLEN] = {0};
    std::string ipaddress;
    if (inet_ntop(
        AF_INET6, &m_ipaddress, cstraddress, sizeof(char)*INET6_ADDRSTRLEN))
    {
        ipaddress = cstraddress;
    }
    return ipaddress;
}


////////////////////////////////////////////////////////////////////////////////
//  IPAddress6 copy operator                                                  //
////////////////////////////////////////////////////////////////////////////////
IPAddress6& IPAddress6::operator=(const IPAddress6& ipaddress)
{
    m_ipaddress.s6_addr16[0] = ipaddress.m_ipaddress.s6_addr16[0];
    m_ipaddress.s6_addr16[1] = ipaddress.m_ipaddress.s6_addr16[1];
    m_ipaddress.s6_addr16[2] = ipaddress.m_ipaddress.s6_addr16[2];
    m_ipaddress.s6_addr16[3] = ipaddress.m_ipaddress.s6_addr16[3];
    m_ipaddress.s6_addr16[4] = ipaddress.m_ipaddress.s6_addr16[4];
    m_ipaddress.s6_addr16[5] = ipaddress.m_ipaddress.s6_addr16[5];
    m_ipaddress.s6_addr16[6] = ipaddress.m_ipaddress.s6_addr16[6];
    m_ipaddress.s6_addr16[7] = ipaddress.m_ipaddress.s6_addr16[7];
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//  IPAddress6 equal to operator                                              //
////////////////////////////////////////////////////////////////////////////////
bool IPAddress6::operator==(const IPAddress6& ipaddress)
{
    return ((m_ipaddress.s6_addr16[0] == ipaddress.m_ipaddress.s6_addr16[0]) &&
            (m_ipaddress.s6_addr16[1] == ipaddress.m_ipaddress.s6_addr16[1]) &&
            (m_ipaddress.s6_addr16[2] == ipaddress.m_ipaddress.s6_addr16[2]) &&
            (m_ipaddress.s6_addr16[3] == ipaddress.m_ipaddress.s6_addr16[3]) &&
            (m_ipaddress.s6_addr16[4] == ipaddress.m_ipaddress.s6_addr16[4]) &&
            (m_ipaddress.s6_addr16[5] == ipaddress.m_ipaddress.s6_addr16[5]) &&
            (m_ipaddress.s6_addr16[6] == ipaddress.m_ipaddress.s6_addr16[6]) &&
            (m_ipaddress.s6_addr16[7] == ipaddress.m_ipaddress.s6_addr16[7]));
}
