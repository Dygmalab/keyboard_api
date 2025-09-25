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
#include "kbd_if.h"

struct kbdif
{
    /* Driver-specific Instance */
    void * p_instance;

    /* Handlers */
    const kbdif_handlers_t * handlers;
};

static result_t _init( kbdif_t * p_kbdif, const kbdif_conf_t * p_conf )
{
    p_kbdif->p_instance = p_conf->p_instance;
    p_kbdif->handlers = p_conf->handlers;

    return RESULT_OK;
}

/*******************************************************************/
/*                          Link List API                          */
/*******************************************************************/

result_t kbdif_init( kbdif_t ** pp_kbdif, const kbdif_conf_t * p_conf )
{
    result_t result = RESULT_ERR;

    *pp_kbdif = heap_alloc( sizeof( kbdif_t ) );

    result = _init( *pp_kbdif, p_conf );
    EXIT_IF_ERR( result, "_init failed" );

_EXIT:
    return result;
}

kbdapi_event_result_t kbdif_key_event( kbdif_t * p_kbdif, kbdapi_key_t * p_key )
{
    if( p_kbdif == NULL || p_kbdif->handlers->key_event_cb == NULL )
    {
        return KBDAPI_EVENT_RESULT_IGNORED;
    }

    return p_kbdif->handlers->key_event_cb( p_kbdif->p_instance, p_key );
}

kbdapi_event_result_t kbdif_command_event( kbdif_t * p_kbdif, const char * p_command )
{
    if( p_kbdif == NULL || p_kbdif->handlers->command_event_cb == NULL )
    {
        return KBDAPI_EVENT_RESULT_IGNORED;
    }

    return p_kbdif->handlers->command_event_cb( p_kbdif->p_instance, p_command );
}
