/*
 * The MIT License (MIT)
 *
 * Copyright (C) 2026  Dygma Lab S.L.
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

#ifndef __KBD_PWR_IF_H_
#define __KBD_PWR_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "kbd_core.h"

/*****************************************************/
/*                KBD power functions                */
/*****************************************************/

typedef void (* kbdpwr_sleep_postpone_fn)( void );

extern void kbdpwr_sleep_postpone( void );

/*****************************************************/
/*                KBD power interface                */
/*****************************************************/

typedef struct
{
    kbdpwr_sleep_postpone_fn sleep_postpone_fn;
} kbdpwrif_config_t;

extern result_t kbdpwrif_init( const kbdpwrif_config_t * p_config );

#ifdef __cplusplus
}
#endif

#endif /* __KBD_PWR_IF_H_ */
