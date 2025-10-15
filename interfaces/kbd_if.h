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

#ifndef __KBD_IF_H_
#define __KBD_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "kbd_core.h"

/* Keyboard interfaace handlers */

typedef kbdapi_event_result_t( *kbdif_key_event_cb )( void * p_instance, kbdapi_key_t * p_key );
typedef kbdapi_event_result_t( *kbdif_command_event_cb )( void * p_instance, const char * p_command );
typedef kbdapi_event_result_t( *kbdif_led_layer_change_event_cb )( void * p_instance, kbdapi_led_layer_id_t layer_id );
typedef kbdapi_event_result_t( *kbdif_led_effect_change_event_cb )( void * p_instance, kbdapi_led_effect_action_t action );

typedef struct
{
    /* Receiving direction */
    kbdif_key_event_cb key_event_cb;
    kbdif_command_event_cb command_event_cb;
    kbdif_led_layer_change_event_cb led_layer_change_event_cb;
    kbdif_led_effect_change_event_cb led_effect_change_event_cb;
} kbdif_handlers_t;

typedef struct
{
    /* Driver-specific Instance */
    void * p_instance;

    /* Handlers */
    const kbdif_handlers_t * handlers;

} kbdif_conf_t;

typedef struct kbdif kbdif_t;

extern result_t kbdif_init( kbdif_t ** pp_kbdif, const kbdif_conf_t * p_conf );
extern kbdapi_event_result_t kbdif_key_event( kbdif_t * p_kbdif, kbdapi_key_t * p_key );
extern kbdapi_event_result_t kbdif_command_event( kbdif_t * p_kbdif, const char * p_command );
extern kbdapi_event_result_t kbdif_led_layer_change_event( kbdif_t * p_kbdif, kbdapi_led_layer_id_t layer_id );
extern kbdapi_event_result_t kbdif_led_effect_change_event( kbdif_t * p_kbdif, kbdapi_led_effect_action_t action );

#ifdef __cplusplus
}
#endif

#endif /* __KBD_IF_H_ */
