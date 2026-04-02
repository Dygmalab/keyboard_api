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

#include "kbd_base.h"
#include "kbd_if_manager.h"

#include "keyboard_api.h"

typedef struct kbdapi
{
    /* Key reporting */
    kbdapi_key_report_lock_t key_report_lock_id;
    uint32_t key_report_lock_cnt;
} kbdapi_t;

static kbdapi_t kbdapi;

static result_t _key_report_init( kbdapi_t * p_kbdapi );

static result_t _init( kbdapi_t * p_kbdapi, const kbdapi_config_t * p_config )
{
    result_t result = RESULT_ERR;

    result = kbd_base_init();
    EXIT_IF_ERR( result, "kbd_base_init failed" );

    result = kbdifmgr_init();
    EXIT_IF_ERR( result, "kbdifmgr_init failed" );

    result = kbdtimif_init( &p_config->kbdtimif );
    EXIT_IF_ERR( result, "kbdtimif_init failed" );

    result = _key_report_init( p_kbdapi );
    EXIT_IF_ERR( result, "_key_report_init failed" );

_EXIT:
    return result;
}

/*************************************************/
/*                 Key reporting                 */
/*************************************************/

static result_t _key_report_init( kbdapi_t * p_kbdapi )
{
    p_kbdapi->key_report_lock_id = 0;
    p_kbdapi->key_report_lock_cnt = 0;

    return RESULT_OK;
}

static result_t _key_report_lock_init( kbdapi_t * p_kbdapi, kbdapi_key_report_lock_t * p_lock )
{
    *p_lock = 0;

    return RESULT_OK;
}

static result_t _key_report_enable( kbdapi_t * p_kbdapi, kbdapi_key_report_lock_t * p_lock )
{
    result_t result = RESULT_ERR;

    if( *p_lock == 0 )
    {
        /* The key is already unlocked */
        return RESULT_OK;
    }

    ASSERT_DYGMA( p_kbdapi->key_report_lock_cnt != 0, "KBDAPI report lock not expected to be 0 at this point" );

    /* Unlock the key */
    *p_lock = 0;
    p_kbdapi->key_report_lock_cnt--;

    if( p_kbdapi->key_report_lock_cnt != 0 )
    {
        /* There are still other active locks */
        return RESULT_OK;
    }

    /* Enable the Key reporting */
    result = kbd_base_key_report_enable();
    EXIT_IF_ERR( result, "kbd_base_key_report_enable failed" );

_EXIT:
    return result;
}

static result_t _key_report_disable( kbdapi_t * p_kbdapi, kbdapi_key_report_lock_t * p_lock )
{
    result_t result = RESULT_ERR;

    if( *p_lock != 0 )
    {
        /* The key is already locked */
        return RESULT_OK;
    }

    /* Lock the key */
    p_kbdapi->key_report_lock_id++;
    *p_lock = p_kbdapi->key_report_lock_id;

    p_kbdapi->key_report_lock_cnt++;

    if( p_kbdapi->key_report_lock_cnt > 1 )
    {
        /* The Key reporting was already disabled before */
        return RESULT_OK;
    }

    /* Enable the Key reporting */
    result = kbd_base_key_report_disable();
    EXIT_IF_ERR( result, "kbd_base_key_report_disable failed" );

_EXIT:
    return result;
}

/*************************************************/
/*                    KBD API                    */
/*************************************************/

result_t kbdapi_init( const kbdapi_config_t * p_config )
{
    return _init( &kbdapi, p_config );
}

result_t kbdapi_key_report_lock_init( kbdapi_key_report_lock_t * p_lock )
{
    return _key_report_lock_init( &kbdapi, p_lock );
}

result_t kbdapi_key_report_enable( kbdapi_key_report_lock_t * p_lock )
{
    return _key_report_enable( &kbdapi, p_lock );
}

result_t kbdapi_key_report_disable( kbdapi_key_report_lock_t * p_lock )
{
    return _key_report_disable( &kbdapi, p_lock );
}
