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
//     Network/Lin/IPAddress4.h : IPv4 address management for Linux           //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_NETWORK_LIN_IPADDRESS4_HEADER
#define VOS_NETWORK_LIN_IPADDRESS4_HEADER

    #include "../../System/System.h"

    #include <arpa/inet.h>
    #include <netdb.h>

    #include <cstdint>
    #include <cstring>
    #include <string>


    ////////////////////////////////////////////////////////////////////////////
    //  IPAddress4 class definition                                           //
    ////////////////////////////////////////////////////////////////////////////
    class IPAddress4
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  IPAddress4 default constructor                                //
            ////////////////////////////////////////////////////////////////////
            IPAddress4();

            ////////////////////////////////////////////////////////////////////
            //  IPAddress4 copy constructor                                   //
            ////////////////////////////////////////////////////////////////////
            IPAddress4(const IPAddress4& ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  IPAddress4 destructor                                         //
            ////////////////////////////////////////////////////////////////////
            ~IPAddress4();


            ////////////////////////////////////////////////////////////////////
            //  Set IP address v4 representation                              //
            ////////////////////////////////////////////////////////////////////
            void setAddress(in_addr ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  Set IP address v4 integer                                     //
            ////////////////////////////////////////////////////////////////////
            void setInteger(uint32_t ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  Set IP address v4 string                                      //
            ////////////////////////////////////////////////////////////////////
            bool setString(const std::string& ipaddress);


            ////////////////////////////////////////////////////////////////////
            //  Resolve host name into IP address                             //
            ////////////////////////////////////////////////////////////////////
            bool resolveHostName(const std::string& hostName);


            ////////////////////////////////////////////////////////////////////
            //  Get IP address v4 representation                              //
            ////////////////////////////////////////////////////////////////////
            in_addr getAddress();

            ////////////////////////////////////////////////////////////////////
            //  Get IP address v4 integer                                     //
            ////////////////////////////////////////////////////////////////////
            uint32_t getInteger();

            ////////////////////////////////////////////////////////////////////
            //  Get IP address v4 string                                      //
            ////////////////////////////////////////////////////////////////////
            std::string getString();


            ////////////////////////////////////////////////////////////////////
            //  IPAddress4 copy operator                                      //
            ////////////////////////////////////////////////////////////////////
            IPAddress4& operator=(const IPAddress4& ipaddress);

            ////////////////////////////////////////////////////////////////////
            //  IPAddress4 equal to operator                                  //
            ////////////////////////////////////////////////////////////////////
            bool operator==(const IPAddress4& ipaddress);


        private:
            in_addr         m_ipaddress;        // IPAddress v4 representation
    };


#endif // VOS_NETWORK_LIN_IPADDRESS4_HEADER
