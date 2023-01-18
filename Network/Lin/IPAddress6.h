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
//     Network/Lin/IPAddress6.h : IPv6 address management for Linux           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_NETWORK_LIN_IPADDRESS6_HEADER
#define VOS_NETWORK_LIN_IPADDRESS6_HEADER

    #include "../../System/System.h"

    #include <arpa/inet.h>
    #include <netdb.h>

    #include <cstdint>
    #include <cstring>
    #include <string>


    ////////////////////////////////////////////////////////////////////////////
    //  IPAddress6 class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class IPAddress6
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  IPAddress6 default constructor                                //
            ////////////////////////////////////////////////////////////////////
            IPAddress6();

            ////////////////////////////////////////////////////////////////////
            //  IPAddress6 copy constructor                                   //
            ////////////////////////////////////////////////////////////////////
            IPAddress6(const IPAddress6& ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  IPAddress6 destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~IPAddress6();


            ////////////////////////////////////////////////////////////////////
            //  Set IP address v6 representation                              //
            ////////////////////////////////////////////////////////////////////
            void setAddress(in6_addr ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  Set IP address v6 string                                      //
            ////////////////////////////////////////////////////////////////////
            inline bool setString(const std::string& ipaddress)
            {
                return (inet_pton(AF_INET6,ipaddress.c_str(),&m_ipaddress)==1);
            }


            ////////////////////////////////////////////////////////////////////
            //  Resolve host name into IP address                             //
            ////////////////////////////////////////////////////////////////////
            bool resolveHostName(const std::string& hostName);


            ////////////////////////////////////////////////////////////////////
            //  Get IP address v6 representation                              //
            ////////////////////////////////////////////////////////////////////
            inline in6_addr getAddress()
            {
                return m_ipaddress;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get IP address v6 string                                      //
            ////////////////////////////////////////////////////////////////////
            std::string getString();


            ////////////////////////////////////////////////////////////////////
            //  IPAddress6 copy operator                                      //
            ////////////////////////////////////////////////////////////////////
            IPAddress6& operator=(const IPAddress6& ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  IPAddress6 equal to operator                                  //
            ////////////////////////////////////////////////////////////////////
            bool operator==(const IPAddress6& ipaddress);


        private:
            in6_addr        m_ipaddress;        // IPAddress v6 representation
    };


#endif // VOS_NETWORK_LIN_IPADDRESS6_HEADER
