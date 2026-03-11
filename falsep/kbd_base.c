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

#include "kbdfal_ll_base.h"

result_t kbd_base_init( void )
{
    return kbdfal_ll_base_init();
}

result_t kbd_base_key_report_enable( void )
{
    return kbdfal_ll_base_key_report_enable();
}

result_t kbd_base_key_report_disable( void )
{
    return kbdfal_ll_base_key_report_disable();
}

result_t kbd_base_kbdif_set( kbdif_t * p_kbdif )
{
    return kbdfal_ll_base_kbdif_set( p_kbdif );
}
