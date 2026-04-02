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

#include "kbd_pwr_if.h"

typedef struct
{
    /* Interface functions */
    kbdpwr_sleep_postpone_fn sleep_postpone_fn;
} kbdpwrif_t;

static kbdpwrif_t kbdpwrif;

/*****************************************************/
/*                KBD power functions                */
/*****************************************************/

static INLINE void _sleep_postpone( kbdpwrif_t * p_kbdpwrif )
{
    p_kbdpwrif->sleep_postpone_fn();
}

void kbdpwr_sleep_postpone( void )
{
    _sleep_postpone( &kbdpwrif );
}

/*****************************************************/
/*                KBD power interface                */
/*****************************************************/

static INLINE result_t _init( kbdpwrif_t * p_kbdpwrif, const kbdpwrif_config_t * p_config )
{
    ASSERT_DYGMA( p_config != NULL, "KBD Pwr Interface not specified" );
    ASSERT_DYGMA( p_config->sleep_postpone_fn != NULL, "KBD Pwr Interface sleep_postpone_fn not specified" );

    /* Set the interface functions */
    p_kbdpwrif->sleep_postpone_fn = p_config->sleep_postpone_fn;

    return RESULT_OK;
}

result_t kbdpwrif_init( const kbdpwrif_config_t * p_config )
{
    /* Set the interface functions */
    return _init( &kbdpwrif, p_config );
}
