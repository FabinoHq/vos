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
//     Network/Win/TCPSocket.h : TCPSocket management for Windows             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_NETWORK_WIN_TCPSOCKET_HEADER
#define VOS_NETWORK_WIN_TCPSOCKET_HEADER

    #include "IPAddress4.h"
    #include "IPAddress6.h"

    #include <winsock2.h>
    #include <Ws2tcpip.h>

    #include <cstddef>
    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  TCPSocket IP Address version                                          //
    ////////////////////////////////////////////////////////////////////////////
    enum TCPSocketIPVersion
    {
        TCPSOCKET_NONE = 0,
        TCPSOCKET_IPV4 = 1,
        TCPSOCKET_IPV6 = 2
    };

    ////////////////////////////////////////////////////////////////////////////
    //  TCPSocket invalid socket constant                                     //
    ////////////////////////////////////////////////////////////////////////////
    const UINT_PTR TCPSocketInvalid = INVALID_SOCKET;

    ////////////////////////////////////////////////////////////////////////////
    //  TCPSocket maximum back log (pending connections queue length)         //
    ////////////////////////////////////////////////////////////////////////////
    const int TCPSocketMaxBackLog = SOMAXCONN;


    ////////////////////////////////////////////////////////////////////////////
    //  TCPSocket class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class TCPSocket
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  TCPSocket default constructor                                //
            ////////////////////////////////////////////////////////////////////
            TCPSocket();

            ////////////////////////////////////////////////////////////////////
            //  TCPSocket destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~TCPSocket();


            ////////////////////////////////////////////////////////////////////
            //  Create TCP Socket                                             //
            ////////////////////////////////////////////////////////////////////
            bool createSocket(
                TCPSocketIPVersion ipversion, bool blocking = true);

            ////////////////////////////////////////////////////////////////////
            //  Close TCP Socket                                              //
            ////////////////////////////////////////////////////////////////////
            void closeSocket();


            ////////////////////////////////////////////////////////////////////
            //  Bind TCP Socket                                               //
            ////////////////////////////////////////////////////////////////////
            bool bindSocket(uint16_t port);

            ////////////////////////////////////////////////////////////////////
            //  Listen bound port                                             //
            ////////////////////////////////////////////////////////////////////
            bool listenPort();

            ////////////////////////////////////////////////////////////////////
            //  Accept incoming connection (IPv4)                             //
            ////////////////////////////////////////////////////////////////////
            bool acceptConnection(TCPSocket& socket, IPAddress4& ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  Accept incoming connection (IPv6)                             //
            ////////////////////////////////////////////////////////////////////
            bool acceptConnection(TCPSocket& socket, IPAddress6& ipaddress);


            ////////////////////////////////////////////////////////////////////
            //  Connect TCP socket to IP address (IPv4)                       //
            ////////////////////////////////////////////////////////////////////
            bool connectSocket(IPAddress4& ipaddress, uint16_t port);

            ////////////////////////////////////////////////////////////////////
            //  Connect TCP socket to IP address (IPv6)                       //
            ////////////////////////////////////////////////////////////////////
            bool connectSocket(IPAddress6& ipaddress, uint16_t port);


            ////////////////////////////////////////////////////////////////////
            //  Send data over TCP                                            //
            ////////////////////////////////////////////////////////////////////
            bool sendData(const char* data, size_t size);

            ////////////////////////////////////////////////////////////////////
            //  Receive data over TCP                                         //
            ////////////////////////////////////////////////////////////////////
            bool receiveData(char* data, size_t size);


        private:
            ////////////////////////////////////////////////////////////////////
            //  TCPSocket private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            TCPSocket(const TCPSocket&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  TCPSocket private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            TCPSocket& operator=(const TCPSocket&) = delete;


        private:
            UINT_PTR                m_handle;       // TCPSocket handle
            TCPSocketIPVersion      m_ipversion;    // TCPSocket IP version
    };


#endif // VOS_NETWORK_WIN_TCPSOCKET_HEADER
