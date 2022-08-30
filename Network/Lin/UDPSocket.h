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
//     Network/Win/UDPSocket.h : UDPSocket management for Windows             //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_NETWORK_WIN_UDPSOCKET_HEADER
#define VOS_NETWORK_WIN_UDPSOCKET_HEADER

    #include "../../System/System.h"
    #include "IPAddress4.h"
    #include "IPAddress6.h"

    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <netinet/udp.h>
    #include <arpa/inet.h>
    #include <netdb.h>
    #include <fcntl.h>
    #include <unistd.h>

    #include <cstddef>
    #include <cstdint>
    #include <cstring>


    ////////////////////////////////////////////////////////////////////////////
    //  UDPSocket IP Address version                                          //
    ////////////////////////////////////////////////////////////////////////////
    enum UDPSocketIPVersion
    {
        UDPSOCKET_NONE = 0,
        UDPSOCKET_IPV4 = 1,
        UDPSOCKET_IPV6 = 2
    };

    ////////////////////////////////////////////////////////////////////////////
    //  UDPSocket invalid socket constant                                     //
    ////////////////////////////////////////////////////////////////////////////
    const int UDPSocketInvalid = -1;

    ////////////////////////////////////////////////////////////////////////////
    //  UDPSocket maximum back log (pending connections queue length)         //
    ////////////////////////////////////////////////////////////////////////////
    const int UDPSocketMaxBackLog = SOMAXCONN;


    ////////////////////////////////////////////////////////////////////////////
    //  UDPSocket class definition                                            //
    ////////////////////////////////////////////////////////////////////////////
    class UDPSocket
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  UDPSocket default constructor                                 //
            ////////////////////////////////////////////////////////////////////
            UDPSocket();

            ////////////////////////////////////////////////////////////////////
            //  UDPSocket destructor                                          //
            ////////////////////////////////////////////////////////////////////
            ~UDPSocket();


            ////////////////////////////////////////////////////////////////////
            //  Create UDP Socket                                             //
            ////////////////////////////////////////////////////////////////////
            bool createSocket(UDPSocketIPVersion ipversion,
                bool blocking = true);

            ////////////////////////////////////////////////////////////////////
            //  Close UDP Socket                                              //
            ////////////////////////////////////////////////////////////////////
            void closeSocket();


            ////////////////////////////////////////////////////////////////////
            //  Bind UDP Socket                                               //
            ////////////////////////////////////////////////////////////////////
            bool bindSocket(uint16_t port);


            ////////////////////////////////////////////////////////////////////
            //  Send data over UDP (IPv4)                                     //
            ////////////////////////////////////////////////////////////////////
            bool sendData(const char* data, size_t size,
                IPAddress4& ipaddress, uint16_t port);

            ////////////////////////////////////////////////////////////////////
            //  Send data over UDP (IPv6)                                     //
            ////////////////////////////////////////////////////////////////////
            bool sendData(const char* data, size_t size,
                IPAddress6& ipaddress, uint16_t port);

            ////////////////////////////////////////////////////////////////////
            //  Receive data over UDP (IPv4)                                  //
            ////////////////////////////////////////////////////////////////////
            bool receiveData(char* data, size_t size,
                IPAddress4& ipaddress, uint16_t port);

            ////////////////////////////////////////////////////////////////////
            //  Receive data over UDP (IPv6)                                  //
            ////////////////////////////////////////////////////////////////////
            bool receiveData(char* data, size_t size,
                IPAddress6& ipaddress, uint16_t port);


        private:
            ////////////////////////////////////////////////////////////////////
            //  UDPSocket private copy constructor : Not copyable             //
            ////////////////////////////////////////////////////////////////////
            UDPSocket(const UDPSocket&) = delete;

            ////////////////////////////////////////////////////////////////////
            //  UDPSocket private copy operator : Not copyable                //
            ////////////////////////////////////////////////////////////////////
            UDPSocket& operator=(const UDPSocket&) = delete;


        private:
            int                     m_handle;       // UDPSocket handle
            UDPSocketIPVersion      m_ipversion;    // UDPSocket IP version
    };


#endif // VOS_NETWORK_WIN_UDPSOCKET_HEADER
