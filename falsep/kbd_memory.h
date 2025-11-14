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

#ifndef __KBD_MEMORY_H_
#define __KBD_MEMORY_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "kbd_core.h"
#include "kbdfal_memory.h"

    /* Callbacks */
    typedef result_t (* kbdmem_item_request_cb)( void * p_instance, kbdmem_item_type_t item_type, const void ** pp_item );
    typedef result_t (* kbdmem_data_save_cb)( void * p_instance, const void * p_mem_target, const void * p_data, uint16_t data_len );

    typedef struct
    {
        /* Callbacks */
        void * p_instance;
        kbdmem_item_request_cb item_request_cb;
        kbdmem_data_save_cb data_save_cb;
    } kbdmem_config_t;

    extern result_t kbdmem_init( const kbdmem_config_t * p_config );

#ifdef __cplusplus
}
#endif

#endif /* __KBD_MEMORY_H_ */
