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
//     Math/MultiInt.h : Multi precision integer management                   //
////////////////////////////////////////////////////////////////////////////////
#ifndef VOS_MATH_MULTIINT_HEADER
#define VOS_MATH_MULTIINT_HEADER

    #include "../System/System.h"
    #include "Math.h"

    #include <cstdint>


    ////////////////////////////////////////////////////////////////////////////
    //  MultiInt limits constants                                             //
    ////////////////////////////////////////////////////////////////////////////
    const int32_t MutiIntMaxLowValue = 100000000;
    const int32_t MutiIntMaxMediumValue = 100000000;
    const int32_t MutiIntMaxHighValue = 100000000;


    ////////////////////////////////////////////////////////////////////////////
    //  MultiInt class definition                                             //
    ////////////////////////////////////////////////////////////////////////////
    class MultiInt
    {
        public:
            ////////////////////////////////////////////////////////////////////
            //  MultiInt default constructor                                  //
            ////////////////////////////////////////////////////////////////////
            MultiInt()
            {
                sign = 1;
                low = 0;
                medium = 0;
                high = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt copy constructor                                     //
            ////////////////////////////////////////////////////////////////////
            MultiInt(const MultiInt& val)
            {
                sign = val.sign;
                low = val.low;
                medium = val.medium;
                high = val.high;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt components constructor                               //
            ////////////////////////////////////////////////////////////////////
            MultiInt(int32_t signVal,
                int32_t lowVal, int32_t mediumVal, int32_t highVal)
            {
                // Set sign
                sign = ((signVal >= 0) ? 1 : -1);

                // Clamp and set values
                low = Math::clamp(lowVal, 0, (MutiIntMaxLowValue-1));
                medium = Math::clamp(mediumVal, 0, (MutiIntMaxMediumValue-1));
                high = Math::clamp(highVal, 0, (MutiIntMaxHighValue-1));
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt destructor                                           //
            ////////////////////////////////////////////////////////////////////
            ~MultiInt()
            {
                sign = 1;
                low = 0;
                medium = 0;
                high = 0;
            }


            ////////////////////////////////////////////////////////////////////
            //  Reset MultiInt to zero                                        //
            ////////////////////////////////////////////////////////////////////
            inline void reset()
            {
                sign = 1;
                low = 0;
                medium = 0;
                high = 0;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set MultiInt components from a multi integer                  //
            ////////////////////////////////////////////////////////////////////
            inline void set(const MultiInt& val)
            {
                sign = val.sign;
                low = val.low;
                medium = val.medium;
                high = val.high;
            }

            ////////////////////////////////////////////////////////////////////
            //  Set MultiInt components from multiple integers                //
            ////////////////////////////////////////////////////////////////////
            inline void set(int32_t signVal,
                int32_t lowVal, int32_t mediumVal, int32_t highVal)
            {
                // Set sign
                sign = ((signVal >= 0) ? 1 : -1);

                // Clamp and set values
                low = Math::clamp(lowVal, 0, (MutiIntMaxLowValue-1));
                medium = Math::clamp(mediumVal, 0, (MutiIntMaxMediumValue-1));
                high = Math::clamp(highVal, 0, (MutiIntMaxHighValue-1));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set MultiInt sign component                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setSign(int32_t signVal)
            {
                sign = ((signVal >= 0) ? 1 : -1);
            }

            ////////////////////////////////////////////////////////////////////
            //  Set MultiInt low component                                    //
            ////////////////////////////////////////////////////////////////////
            inline void setLow(int32_t lowVal)
            {
                low = Math::clamp(lowVal, 0, (MutiIntMaxLowValue-1));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set MultiInt medium component                                 //
            ////////////////////////////////////////////////////////////////////
            inline void setMedium(int32_t mediumVal)
            {
                medium = Math::clamp(mediumVal, 0, (MutiIntMaxMediumValue-1));
            }

            ////////////////////////////////////////////////////////////////////
            //  Set MultiInt high component                                   //
            ////////////////////////////////////////////////////////////////////
            inline void setHigh(int32_t highVal)
            {
                high = Math::clamp(highVal, 0, (MutiIntMaxHighValue-1));
            }


            ////////////////////////////////////////////////////////////////////
            //  Get MultiInt sign component                                   //
            //  return : Sign component of the multi integer                  //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& signVal()
            {
                return sign;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get MultiInt low component                                    //
            //  return : Low component of the multi integer                   //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& lowVal()
            {
                return low;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get MultiInt medium component                                 //
            //  return : Medium component of the multi integer                //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& mediumVal()
            {
                return medium;
            }

            ////////////////////////////////////////////////////////////////////
            //  Get MultiInt high component                                   //
            //  return : High component of the multi integer                  //
            ////////////////////////////////////////////////////////////////////
            inline int32_t& highVal()
            {
                return high;
            }


            ////////////////////////////////////////////////////////////////////
            //  MultiInt affectation operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt& operator=(const MultiInt& val)
            {
                sign = val.sign;
                low = val.low;
                medium = val.medium;
                high = val.high;
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt addition operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt operator+(const MultiInt& val)
            {
                MultiInt result;
                result.low = low*sign;
                result.medium = medium*sign;
                result.high = high*sign;

                // Add high precision
                result.high += val.high*val.sign;
                clampHigh(result);

                // Add medium precision
                result.medium += val.medium*val.sign;
                clampMedium(result);

                // Add low precision
                result.low += val.low*val.sign;
                clampLow(result);

                // Compute result sign
                computeSign(result);

                // Return result value
                return result;
            }

            inline MultiInt operator+(const int32_t& val)
            {
                MultiInt result;
                result.low = low*sign;
                result.medium = medium*sign;
                result.high = high*sign;

                // Add high precision
                result.high += val;
                clampHigh(result);

                // Clamp medium precision
                clampMedium(result);

                // Clamp low precision
                clampLow(result);

                // Compute result sign
                computeSign(result);

                // Return result value
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt subtraction operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt operator-(const MultiInt& val)
            {
                MultiInt result;
                result.low = low*sign;
                result.medium = medium*sign;
                result.high = high*sign;

                // Subtract high precision
                result.high -= val.high*val.sign;
                clampHigh(result);

                // Subtract medium precision
                result.medium -= val.medium*val.sign;
                clampMedium(result);

                // Subtract low precision
                result.low -= val.low*val.sign;
                clampLow(result);

                // Compute result sign
                computeSign(result);

                // Return result value
                return result;
            }

            inline MultiInt operator-(const int32_t& val)
            {
                MultiInt result;
                result.low = low*sign;
                result.medium = medium*sign;
                result.high = high*sign;

                // Subtract high precision
                result.high -= val;
                clampHigh(result);

                // Clamp medium precision
                clampMedium(result);

                // Clamp low precision
                clampLow(result);

                // Compute result sign
                computeSign(result);

                // Return result value
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt unary plus operator                                  //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt operator+()
            {
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt unary minus operator                                 //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt operator-()
            {
                return MultiInt(-sign, low, medium, high);
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt prefix increment operator                            //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt& operator++()
            {
                low *= sign;
                medium *= sign;
                high *= sign;

                // Increment high precision
                ++high;
                clampHigh();

                // Clamp medium precision
                clampMedium();

                // Clamp low precision
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt postfix increment operator                           //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt operator++(int)
            {
                MultiInt result = *this;
                low *= sign;
                medium *= sign;
                high *= sign;

                // Increment high precision
                ++high;
                clampHigh();

                // Clamp medium precision
                clampMedium();

                // Clamp low precision
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt prefix decrement operator                            //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt& operator--()
            {
                low *= sign;
                medium *= sign;
                high *= sign;

                // Decrement high precision
                --high;
                clampHigh();

                // Clamp medium precision
                clampMedium();

                // Clamp low precision
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt postfix decrement operator                           //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt operator--(int)
            {
                MultiInt result = *this;
                low *= sign;
                medium *= sign;
                high *= sign;

                // Decrement high precision
                --high;
                clampHigh();

                // Clamp medium precision
                clampMedium();

                // Clamp low precision
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return result;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt addition assignment operator                         //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt& operator+=(const MultiInt& val)
            {
                low *= sign;
                medium *= sign;
                high *= sign;

                // Add high precision
                high += val.high*val.sign;
                clampHigh();

                // Add medium precision
                medium += val.medium*val.sign;
                clampMedium();

                // Add low precision
                low += val.low*val.sign;
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return *this;
            }

            inline MultiInt& operator+=(const int32_t& val)
            {
                low *= sign;
                medium *= sign;
                high *= sign;

                // Add high precision
                high += val;
                clampHigh();

                // Clamp medium precision
                clampMedium();

                // Clamp low precision
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt subtraction assignment operator                      //
            ////////////////////////////////////////////////////////////////////
            inline MultiInt& operator-=(const MultiInt& val)
            {
                low *= sign;
                medium *= sign;
                high *= sign;

                // Subtract high precision
                high -= val.high*val.sign;
                clampHigh();

                // Subtract medium precision
                medium -= val.medium*val.sign;
                clampMedium();

                // Subtract low precision
                low -= val.low*val.sign;
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return *this;
            }

            inline MultiInt& operator-=(const int32_t& val)
            {
                low *= sign;
                medium *= sign;
                high *= sign;

                // Subtract high precision
                high -= val;
                clampHigh();

                // Clamp medium precision
                clampMedium();

                // Clamp low precision
                clampLow();

                // Compute result sign
                computeSign();

                // Return result value
                return *this;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt equal to operator                                    //
            ////////////////////////////////////////////////////////////////////
            inline bool operator==(const MultiInt& val)
            {
                return ((sign == val.sign) && (low == val.low) &&
                    (medium == val.medium) && (high == val.high));
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt not equal to operator                                //
            ////////////////////////////////////////////////////////////////////
            inline bool operator!=(const MultiInt& val)
            {
                return ((sign != val.sign) || (low != val.low) ||
                    (medium != val.medium) || (high != val.high));
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt greater than operator                                //
            ////////////////////////////////////////////////////////////////////
            inline bool operator>(const MultiInt& val)
            {
                if (low*sign > (val.low*val.sign))
                {
                    return true;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign > (val.medium*val.sign)))
                {
                    return true;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign == (val.medium*val.sign)) &&
                    (high*sign > (val.high*val.sign)))
                {
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt greater than or equal to operator                    //
            ////////////////////////////////////////////////////////////////////
            inline bool operator>=(const MultiInt& val)
            {
                if (low*sign < (val.low*val.sign))
                {
                    return false;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign < (val.medium*val.sign)))
                {
                    return false;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign == (val.medium*val.sign)) &&
                    (high*sign < (val.high*val.sign)))
                {
                    return false;
                }
                return true;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt less than operator                                   //
            ////////////////////////////////////////////////////////////////////
            inline bool operator<(const MultiInt& val)
            {
                if (low*sign < (val.low*val.sign))
                {
                    return true;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign < (val.medium*val.sign)))
                {
                    return true;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign == (val.medium*val.sign)) &&
                    (high*sign < (val.high*val.sign)))
                {
                    return true;
                }
                return false;
            }

            ////////////////////////////////////////////////////////////////////
            //  MultiInt less than or equal to operator                       //
            ////////////////////////////////////////////////////////////////////
            inline bool operator<=(const MultiInt& val)
            {
                if (low*sign > (val.low*val.sign))
                {
                    return false;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign > (val.medium*val.sign)))
                {
                    return false;
                }
                if ((low*sign == (val.low*val.sign)) &&
                    (medium*sign == (val.medium*val.sign)) &&
                    (high*sign > (val.high*val.sign)))
                {
                    return false;
                }
                return true;
            }


        public:
            ////////////////////////////////////////////////////////////////////
            //  Compute MultiInt sign value                                   //
            ////////////////////////////////////////////////////////////////////
            inline void computeSign()
            {
                int32_t lowSign = Math::sign(low);
                int32_t mediumSign = Math::sign(medium);
                int32_t highSign = Math::sign(high);
                sign = ((lowSign >= 0) ? 1 : -1);

                // Adjust low value
                if ((lowSign != mediumSign) && (low != 0) && (medium != 0))
                {
                    low += mediumSign;
                    medium -= MutiIntMaxMediumValue*mediumSign;
                }
                mediumSign = Math::sign(medium);
                if ((lowSign != highSign) && (low != 0) &&
                    (medium == 0) && (high != 0))
                {
                    low += highSign;
                    medium -= MutiIntMaxMediumValue*highSign;
                }
                mediumSign = Math::sign(medium);

                // Adjust medium value
                if ((mediumSign != highSign) && (medium != 0) && (high != 0))
                {
                    medium += highSign;
                    high -= MutiIntMaxHighValue*highSign;
                }

                // Adjust signs
                if (high < 0)
                {
                    high = -high;
                    sign = -1;
                }
                if (medium < 0)
                {
                    medium = -medium;
                    sign = -1;
                }
                if (low < 0)
                {
                    low = -low;
                }
            }

            inline void computeSign(MultiInt& result)
            {
                int32_t lowSign = Math::sign(result.low);
                int32_t mediumSign = Math::sign(result.medium);
                int32_t highSign = Math::sign(result.high);
                result.sign = ((lowSign >= 0) ? 1 : -1);

                // Adjust low value
                if ((lowSign != mediumSign) &&
                    (result.low != 0) && (result.medium != 0))
                {
                    result.low += mediumSign;
                    result.medium -= MutiIntMaxMediumValue*mediumSign;
                }
                mediumSign = Math::sign(result.medium);
                if ((lowSign != highSign) && (result.low != 0) &&
                    (result.medium == 0) && (result.high != 0))
                {
                    result.low += highSign;
                    result.medium -= MutiIntMaxMediumValue*highSign;
                }
                mediumSign = Math::sign(result.medium);

                // Adjust medium value
                if ((mediumSign != highSign) &&
                    (result.medium != 0) && (result.high != 0))
                {
                    result.medium += highSign;
                    result.high -= MutiIntMaxHighValue*highSign;
                }

                // Adjust signs
                if (result.high < 0)
                {
                    result.high = -result.high;
                    result.sign = -1;
                }
                if (result.medium < 0)
                {
                    result.medium = -result.medium;
                    result.sign = -1;
                }
                if (result.low < 0)
                {
                    result.low = -result.low;
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp MultiInt low precision value                            //
            ////////////////////////////////////////////////////////////////////
            inline void clampLow()
            {
                low = Math::clamp(low,
                    -(MutiIntMaxLowValue-1), (MutiIntMaxLowValue-1)
                );
            }

            inline void clampLow(MultiInt& result)
            {
                result.low = Math::clamp(result.low,
                    -(MutiIntMaxLowValue-1), (MutiIntMaxLowValue-1)
                );
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp MultiInt medium precision value                         //
            ////////////////////////////////////////////////////////////////////
            inline void clampMedium()
            {
                while (medium >= MutiIntMaxMediumValue)
                {
                    ++low;
                    medium -= MutiIntMaxMediumValue;
                }
                while (medium <= (-MutiIntMaxMediumValue))
                {
                    --low;
                    medium += MutiIntMaxMediumValue;
                }
            }

            inline void clampMedium(MultiInt& result)
            {
                while (result.medium >= MutiIntMaxMediumValue)
                {
                    ++result.low;
                    result.medium -= MutiIntMaxMediumValue;
                }
                while (result.medium <= (-MutiIntMaxMediumValue))
                {
                    --result.low;
                    result.medium += MutiIntMaxMediumValue;
                }
            }

            ////////////////////////////////////////////////////////////////////
            //  Clamp MultiInt high precision value                           //
            ////////////////////////////////////////////////////////////////////
            inline void clampHigh()
            {
                while (high >= MutiIntMaxHighValue)
                {
                    ++medium;
                    high -= MutiIntMaxHighValue;
                }
                while (high <= (-MutiIntMaxHighValue))
                {
                    --medium;
                    high += MutiIntMaxHighValue;
                }
            }

            inline void clampHigh(MultiInt& result)
            {
                while (result.high >= MutiIntMaxHighValue)
                {
                    ++result.medium;
                    result.high -= MutiIntMaxHighValue;
                }
                while (result.high <= (-MutiIntMaxHighValue))
                {
                    --result.medium;
                    result.high += MutiIntMaxHighValue;
                }
            }


        public:
            int32_t     sign;       // Multi int sign representation
            int32_t     low;        // Multi int low precision representation
            int32_t     medium;     // Multi int medium precision representation
            int32_t     high;       // Multi int high precision representation
    };


#endif // VOS_MATH_MULTIINT_HEADER
