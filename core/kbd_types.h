/*
 * The MIT License (MIT)
 *
 * Copyright (C) 2025  Dygma Lab S.L.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef __KBD_TYPES_H_
#define __KBD_TYPES_H_


#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*
 * DO NOT MODIFY!!!
 *
 * The Dygma core is used among various Dygma frameworks to assure the same coding philosophy
 * and prevent conflicts when used together in a project.
 */
#ifndef DYGMA_CORE_TYPES_SPECIFIED
#define DYGMA_CORE_TYPES_SPECIFIED

    #define INLINE inline
    #define VOLATILE volatile
    #define PACK __attribute__((__packed__))

    typedef bool bool_t;
    typedef char char_t;

    typedef enum
    {
        RESULT_OK = 0,
        RESULT_ERR,
        RESULT_BUSY,
        RESULT_INCOMPLETE,
    } result_t;

    #define UNUSED(X) (void)X      /* To avoid gcc/g++ warnings */

#endif /* DYGMA_CORE_TYPES_SPECIFIED */

/**************************************************/
/*          Keyboard API key definitions          */
/**************************************************/

typedef enum
{
    KBDAPI_KEY_TYPE_UNSPECIFIED = 0,

    KBDAPI_KEY_TYPE_KBD_1_AND_EXCLAMATION_POINT,
    KBDAPI_KEY_TYPE_KBD_2_AND_AT,
    KBDAPI_KEY_TYPE_KBD_3_AND_POUND,
    KBDAPI_KEY_TYPE_KBD_4_AND_DOLLAR,
    KBDAPI_KEY_TYPE_KBD_5_AND_PERCENT,
    KBDAPI_KEY_TYPE_KBD_6_AND_CARAT,
    KBDAPI_KEY_TYPE_KBD_7_AND_AMPERSAND,
    KBDAPI_KEY_TYPE_KBD_8_AND_ASTERISK,
    KBDAPI_KEY_TYPE_KBD_9_AND_LEFT_PAREN,
    KBDAPI_KEY_TYPE_KBD_0_AND_RIGHT_PAREN,

    KBDAPI_KEY_TYPE_BATTERY_LEVEL,
    KBDAPI_KEY_TYPE_BLUETOOTH_PAIRING,
} kbdapi_key_type_t;

typedef enum
{
    KBDAPI_EVENT_RESULT_IGNORED = 0,
    KBDAPI_EVENT_RESULT_CONSUMED,
} kbdapi_event_result_t;

typedef struct
{
    kbdapi_key_type_t type;

    /* Position */
    uint16_t col;
    uint16_t row;

    /* Flags */
    bool_t is_pressed;      /* True if the key is actually pressed */
    bool_t was_pressed;     /* True if the key was pressed in the previous scan cycle, regardless of whether it is pressed or not in this scan cycle */
    bool_t toggled_on;      /* True if the key has just been pressed */
    bool_t toggled_off;     /* True if the key has just been released */

} kbdapi_key_t;

#endif /* __KBD_TYPES_H_ */
