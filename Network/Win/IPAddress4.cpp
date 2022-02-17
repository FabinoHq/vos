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
//   For more information, please refer to <http://unlicense.org>             //
////////////////////////////////////////////////////////////////////////////////
//    VOS : Virtual Operating System                                          //
//     Network/Win/IPAddress4.cpp : IPv4 address management for Windows       //
////////////////////////////////////////////////////////////////////////////////
#include "IPAddress4.h"


////////////////////////////////////////////////////////////////////////////////
//  IPAddress4 default constructor                                            //
////////////////////////////////////////////////////////////////////////////////
IPAddress4::IPAddress4() :
m_ipaddress()
{
    m_ipaddress.s_addr = 0;
}

////////////////////////////////////////////////////////////////////////////////
//  IPAddress4 copy constructor                                               //
////////////////////////////////////////////////////////////////////////////////
IPAddress4::IPAddress4(const IPAddress4& ipaddress) :
m_ipaddress()
{
    m_ipaddress.s_addr = ipaddress.m_ipaddress.s_addr;
}

////////////////////////////////////////////////////////////////////////////////
//  IPAddress4 destructor                                                     //
////////////////////////////////////////////////////////////////////////////////
IPAddress4::~IPAddress4()
{
    m_ipaddress.s_addr = 0;
}


////////////////////////////////////////////////////////////////////////////////
//  Set IP address v4 integer                                                 //
////////////////////////////////////////////////////////////////////////////////
void IPAddress4::setInteger(uint32_t ipaddress)
{
    m_ipaddress.s_addr = htonl(ipaddress);
}

////////////////////////////////////////////////////////////////////////////////
//  Set IP address v4 string                                                  //
////////////////////////////////////////////////////////////////////////////////
bool IPAddress4::setString(const std::string& ipaddress)
{
    return (inet_pton(AF_INET, ipaddress.c_str(), &m_ipaddress) == 1);
}


////////////////////////////////////////////////////////////////////////////////
//  Resolve host name into IP address                                         //
////////////////////////////////////////////////////////////////////////////////
bool IPAddress4::resolveHostName(const std::string& hostName)
{
    addrinfo hints;
    hints.ai_flags = 0;
    hints.ai_family = AF_INET;
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
    sockaddr_in addr;
    addr.sin_family = 0;
    addr.sin_port = 0;
    addr.sin_addr.s_addr = 0;
    addr.sin_zero[0] = 0;
    addr.sin_zero[1] = 0;
    addr.sin_zero[2] = 0;
    addr.sin_zero[3] = 0;
    addr.sin_zero[4] = 0;
    addr.sin_zero[5] = 0;
    addr.sin_zero[6] = 0;
    addr.sin_zero[7] = 0;
    memcpy(&addr, result->ai_addr, sizeof(addr));
    freeaddrinfo(result);

    // Set IP address
    m_ipaddress.s_addr = addr.sin_addr.s_addr;

    // Host name resolved
    return true;
}


////////////////////////////////////////////////////////////////////////////////
//  Get IP address v4 representation                                          //
////////////////////////////////////////////////////////////////////////////////
in_addr IPAddress4::getAddress()
{
    return m_ipaddress;
}

////////////////////////////////////////////////////////////////////////////////
//  Get IP address v4 integer                                                 //
////////////////////////////////////////////////////////////////////////////////
uint32_t IPAddress4::getInteger()
{
    return ntohl(m_ipaddress.s_addr);
}

////////////////////////////////////////////////////////////////////////////////
//  Get IP address v4 string                                                  //
////////////////////////////////////////////////////////////////////////////////
std::string IPAddress4::getString()
{
    char cstraddress[INET_ADDRSTRLEN] = {0};
    std::string ipaddress;
    if (inet_ntop(
        AF_INET, &m_ipaddress, cstraddress, sizeof(char)*INET_ADDRSTRLEN))
    {
        ipaddress = cstraddress;
    }
    return ipaddress;
}


////////////////////////////////////////////////////////////////////////////////
//  IPAddress4 copy operator                                                  //
////////////////////////////////////////////////////////////////////////////////
IPAddress4& IPAddress4::operator=(const IPAddress4& ipaddress)
{
    m_ipaddress.s_addr = ipaddress.m_ipaddress.s_addr;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
//  IPAddress4 equal to operator                                              //
////////////////////////////////////////////////////////////////////////////////
bool IPAddress4::operator==(const IPAddress4& ipaddress)
{
    return (m_ipaddress.s_addr == ipaddress.m_ipaddress.s_addr);
}
