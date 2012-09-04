
#ifndef _COMMON_H
#define _COMMON_H
//#include<string.h>
//------------------------------------------------------------------------------
//      Definitions
//------------------------------------------------------------------------------
#define AT91SAM9261
#ifndef inline
    #define inline __inline
#endif
#include "AT91SAM9261.h"
//------------------------------------------------------------------------------
//      Types
//------------------------------------------------------------------------------
#define UDP
#define UDP_INTERNAL_PULLUP_BY_MATRIX
#define FULLSPEED
#define USB_ENDPOINT0_MAXPACKETSIZE       8

#define USB_BUS_POWERED
// \brief  Boolean type
//typedef enum {false = 0, true = 1} bool;

// \brief  Generic callback function type
//
//         Since ARM Procedure Call standard allow for 4 parameters to be
//         stored in r0-r3 instead of being pushed on the stack, functions with
//         less than 4 parameters can be cast into a callback in a transparent
//         way.
typedef void (*Callback_f)(unsigned int, unsigned int,
                           unsigned int, unsigned int);

//------------------------------------------------------------------------------
//      Macros
//------------------------------------------------------------------------------

// Set or clear flag(s) in a register
#define SET(register, flags)        ((register) = (register) | (flags))
#define CLEAR(register, flags)      ((register) &= ~(flags))

// Poll the status of flags in a register
#define ISSET(register, flags)      (((register) & (flags)) == (flags))
#define ISCLEARED(register, flags)  (((register) & (flags)) == 0)

// Returns the higher/lower byte of a word
#define HBYTE(word)                 ((unsigned char) ((word) >> 8))
#define LBYTE(word)                 ((unsigned char) ((word) & 0x00FF))

//! \brief  Converts a byte array to a word value using the big endian format
#define WORDB(bytes)            ((unsigned short) ((bytes[0] << 8) | bytes[1]))

//! \brief  Converts a byte array to a word value using the big endian format
#define WORDL(bytes)            ((unsigned short) ((bytes[1] << 8) | bytes[0]))

//! \brief  Converts a byte array to a dword value using the big endian format
#define DWORDB(bytes)   ((unsigned int) ((bytes[0] << 24) | (bytes[1] << 16) \
                                         | (bytes[2] << 8) | bytes[3]))

//! \brief  Converts a byte array to a dword value using the big endian format
#define DWORDL(bytes)   ((unsigned int) ((bytes[3] << 24) | (bytes[2] << 16) \
                                         | (bytes[1] << 8) | bytes[0]))

//! \brief  Stores a dword value in a byte array, in big endian format
#define STORE_DWORDB(dword, bytes) \
    bytes[0] = (unsigned char) ((dword >> 24) & 0xFF); \
    bytes[1] = (unsigned char) ((dword >> 16) & 0xFF); \
    bytes[2] = (unsigned char) ((dword >> 8) & 0xFF); \
    bytes[3] = (unsigned char) (dword & 0xFF);

//! \brief  Stores a word value in a byte array, in big endian format
#define STORE_WORDB(word, bytes) \
    bytes[0] = (unsigned char) ((word >> 8) & 0xFF); \
    bytes[1] = (unsigned char) (word & 0xFF);

//------------------------------------------------------------------------------
//      Inline functions
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//! \brief  Copies a structure in a buffer
//! \param  pSource Data to copy
//! \param  pDest   Buffer in which to copy the data
//------------------------------------------------------------------------------

#if 0
extern inline void copy(void *pSource, void *pDest, unsigned int dLength)
{
    unsigned int dI;

    for (dI = 0; dI < dLength; dI++) {

        *((char *) pDest) = *((char *) pSource);
        ((char *) pDest)++;
        ((char *) pSource)++;
    }
}
#endif

//------------------------------------------------------------------------------
// \brief  Returns the minimum value between two integers
// \param  dValue1 First value to compare
// \param  dValue2 Second value to compare
// \return Minimum value between two integers
//------------------------------------------------------------------------------

#if 0
unsigned int min1(unsigned int dValue1, unsigned int dValue2)
{
    if (dValue1 < dValue2) {

        return dValue1;
    }
    else {

        return dValue2;
    }
}
#endif
#define min1(a, b) (a < b ? a : b)

//------------------------------------------------------------------------------
// \brief  Returns the index of the last set (1) bit in an integer
// \param  dValue Integer value to parse
// \return Position of the leftmost set bit in the integer
//------------------------------------------------------------------------------
extern inline signed char lastSetBit(unsigned int dValue)
{
    signed char bIndex = -1;

    if (dValue & 0xFFFF0000) {

        bIndex += 16;
        dValue >>= 16;
    }

    if (dValue & 0xFF00) {

        bIndex += 8;
        dValue >>= 8;
    }

    if (dValue & 0xF0) {

        bIndex += 4;
        dValue >>= 4;
    }

    if (dValue & 0xC) {

        bIndex += 2;
        dValue >>= 2;
    }

    if (dValue & 0x2) {

        bIndex += 1;
        dValue >>= 1;
    }

    if (dValue & 0x1) {

        bIndex++;
    }

    return bIndex;
}

#ifdef PRINF_DEBUG_ENABLE
#define printk1 printk

#else
#define printk1(...)
#endif // PRINF_DEBUG

#endif // _COMMON_H

/*@}*/

