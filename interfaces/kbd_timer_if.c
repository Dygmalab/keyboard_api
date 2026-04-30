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

#include "kbd_timer_if.h"

typedef struct
{
    /* Interface functions */
    kbdtimer_get_system_ms_fn get_system_ms_fn;
    kbdtimer_set_ms_fn set_ms_fn;
    kbdtimer_check_fn check_fn;
} kbdtimif_t;

static kbdtimif_t kbdtimif;

/*****************************************************/
/*                KBD timer functions                */
/*****************************************************/

static INLINE uint32_t _get_system_ms( kbdtimif_t * p_kbdtimif )
{
    return p_kbdtimif->get_system_ms_fn( );
}

static INLINE void _timer_set_ms( kbdtimif_t * p_kbdtimif, kbdtimer_t * p_timer, uint32_t ms )
{
    p_kbdtimif->set_ms_fn( p_timer, ms );
}

static INLINE bool _timer_check( kbdtimif_t * p_kbdtimif, kbdtimer_t * p_timer )
{
    return p_kbdtimif->check_fn( p_timer );
}

uint32_t kbdtimer_get_system_ms( void )
{
    return _get_system_ms( &kbdtimif );
}

void kbdtimer_set_ms( kbdtimer_t * p_timer, uint32_t ms )
{
    _timer_set_ms( &kbdtimif, p_timer, ms );
}

bool kbdtimer_check( kbdtimer_t * p_timer )
{
    return _timer_check( &kbdtimif, p_timer );
}

/*****************************************************/
/*                KBD timer interface                */
/*****************************************************/

static INLINE result_t _init( kbdtimif_t * p_kbdtimif, const kbdtimif_config_t * p_config )
{
    ASSERT_DYGMA( p_config != NULL, "KBD Timer Interface not specified" );
    ASSERT_DYGMA( p_config->get_system_ms_fn != NULL, "KBD Timer Interface get_system_ms_fn not specified" );
    ASSERT_DYGMA( p_config->set_ms_fn != NULL, "KBD Timer Interface set_ms_fn not specified" );
    ASSERT_DYGMA( p_config->check_fn != NULL, "KBD Timer Interface check_fn not specified" );

    /* Set the interface functions */
    p_kbdtimif->get_system_ms_fn = p_config->get_system_ms_fn;
    p_kbdtimif->set_ms_fn = p_config->set_ms_fn;
    p_kbdtimif->check_fn = p_config->check_fn;

    return RESULT_OK;
}

result_t kbdtimif_init( const kbdtimif_config_t * p_config )
{
    /* Set the interface functions */
    return _init( &kbdtimif, p_config );
}
