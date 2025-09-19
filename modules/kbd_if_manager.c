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

#include "dl_middleware.h"
#include "kbd_base.h"
#include "kbd_if_manager.h"

typedef struct
{
    linklist_t * p_kbdiflist;

    /* Low-level keyboard interface */
    kbdif_t * p_kbdif_ll;
} kbdifmgr_t;

static kbdifmgr_t kbdifmgr;
static const kbdif_handlers_t kbdif_ll_handlers;

static INLINE result_t _kbdif_ll_init( kbdifmgr_t * p_kbdifmgr )
{
    result_t result = RESULT_ERR;
    kbdif_conf_t config;

    /* Prepare the low-level keyboard interface configuration */
    config.p_instance = p_kbdifmgr;
    config.handlers = &kbdif_ll_handlers;

    result = kbdif_init( &p_kbdifmgr->p_kbdif_ll, &config );
    EXIT_IF_ERR( result, "kbdif_init failed" );

    /* Register the low-level keyboard interface */
    result = kbd_base_kbdif_set( p_kbdifmgr->p_kbdif_ll );
    EXIT_IF_ERR( result, "kbd_base_kbdif_set failed" );

_EXIT:
    return result;
}

static INLINE result_t _init( kbdifmgr_t * p_kbdifmgr )
{
    result_t result = RESULT_ERR;

    /* Initialize the keyboard interface list */
    result = linklist_init( &p_kbdifmgr->p_kbdiflist );
    EXIT_IF_ERR( result, "linklist_init failed" );

    /* Initialize the low-level keyboard inteface */
    result = _kbdif_ll_init( p_kbdifmgr );
    EXIT_IF_ERR( result, "_kbdif_ll_init failed" );

_EXIT:
    return result;
}

/**********************************************/
/*        Low level keyboard interface        */
/**********************************************/

static kbdapi_event_result_t _kbdif_ll_key_event_cb( void * p_instance, kbdapi_key_t * p_key )
{
    kbdifmgr_t * p_kbdifmgr = (kbdifmgr_t *)p_instance;

#warning "Continue here"

    return KBDAPI_EVENT_RESULT_IGNORED;
}

static const kbdif_handlers_t kbdif_ll_handlers =
{
    .key_event_cb = _kbdif_ll_key_event_cb,
};

/**********************************************/
/*       Keyboard Interface Manager API       */
/**********************************************/

result_t kbdifmgr_init( void )
{
    return _init( &kbdifmgr );
}
