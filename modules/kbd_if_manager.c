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

static INLINE result_t _add( kbdifmgr_t * p_kbdifmgr, kbdif_t * p_kbdif )
{
    result_t result = RESULT_ERR;

    /* Add the kbdif to the linked list */
    result = linklist_add( p_kbdifmgr->p_kbdiflist, p_kbdif );
    EXIT_IF_ERR( result, "linklist_add failed" );

_EXIT:
    return result;
}

/**********************************************/
/*         Keyboard interface events          */
/**********************************************/

typedef kbdapi_event_result_t(* kbdif_event_fn)( kbdif_t * p_kbdif, void * p_event_data );

typedef struct
{
    /* NOTE: This structure is here mainly to solve the 'const' warning. However, when there is
     *       an event callback with multiple parameters, _event_data_t structure with multiple
     *       items is the way to push the p_event_data through the _kbdiflist_events_process.
     */
    const char * p_command;
} command_event_data_t;

static kbdapi_event_result_t _kbdif_key_event( kbdif_t * p_kbdif, void * p_event_data )
{
    kbdapi_key_t * p_key = (kbdapi_key_t *)p_event_data;

    return kbdif_key_event( p_kbdif, p_key );
}

static kbdapi_event_result_t _kbdif_command_event( kbdif_t * p_kbdif, void * p_event_data )
{
    command_event_data_t * p_command_event_data = (command_event_data_t *)p_event_data;

    return kbdif_command_event( p_kbdif, p_command_event_data->p_command );
}

static kbdapi_event_result_t _kbdiflist_events_process( kbdifmgr_t * p_kbdifmgr, kbdif_event_fn event_fn, void * p_event_data )
{
    kbdapi_event_result_t kbdapi_event_result = KBDAPI_EVENT_RESULT_IGNORED;
    kbdif_t * p_kbdif;

    /* Set the first Linked List item */
    linklist_nav_head( p_kbdifmgr->p_kbdiflist );

    do
    {
        p_kbdif = ( kbdif_t *)linklist_get( p_kbdifmgr->p_kbdiflist );

        if( p_kbdif == NULL )
        {
            /* No more items in the kbdif list */
            break;
        }

        kbdapi_event_result = event_fn( p_kbdif, p_event_data );

        /* Navigate to the next kbdif in the list */
        linklist_nav_next( p_kbdifmgr->p_kbdiflist );
    } while( kbdapi_event_result != KBDAPI_EVENT_RESULT_CONSUMED );

    return kbdapi_event_result;
}

/**********************************************/
/*        Low level keyboard interface        */
/**********************************************/

static kbdapi_event_result_t _kbdif_ll_key_event_cb( void * p_instance, kbdapi_key_t * p_key )
{
    kbdifmgr_t * p_kbdifmgr = (kbdifmgr_t *)p_instance;

    return _kbdiflist_events_process( p_kbdifmgr, _kbdif_key_event, p_key );
}

static kbdapi_event_result_t _kbdif_ll_command_event_cb( void * p_instance, const char * p_command )
{
    kbdifmgr_t * p_kbdifmgr = (kbdifmgr_t *)p_instance;
    command_event_data_t command_event_data;

    command_event_data.p_command = p_command;

    return _kbdiflist_events_process( p_kbdifmgr, _kbdif_command_event, &command_event_data );
}

static const kbdif_handlers_t kbdif_ll_handlers =
{
    .key_event_cb = _kbdif_ll_key_event_cb,
    .command_event_cb = _kbdif_ll_command_event_cb,
};

/**********************************************/
/*       Keyboard Interface Manager API       */
/**********************************************/

result_t kbdifmgr_init( void )
{
    return _init( &kbdifmgr );
}

result_t kbdifmgr_add( kbdif_t * p_kbdif )
{
    return _add( &kbdifmgr, p_kbdif );
}
