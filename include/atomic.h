/*
 * Copyright (c) 2020 Amazon.com, Inc. or its affiliates.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef KTF_ATOMIC_H
#define KTF_ATOMIC_H

#include <ktf.h>
#include <lib.h>

/* Static declarations */

static inline bool test_bit(unsigned int bit, volatile void *addr) {
    bool status;

    asm volatile (
        "bt %[bit], %[addr];"
        "setc %[status];"
        : [status] "=r" (status)
        : [bit] "Ir" (bit), [addr] "m" (* (uint8_t *) addr)
        : "cc", "memory"
    );

    return status;
}

static inline bool test_and_set_bit(unsigned int bit, volatile void *addr) {
    bool status;

    asm volatile (
        "lock bts %[bit], %[addr];"
        "setc %[status];"
        : [status] "=r" (status)
        : [bit] "Ir" (bit), [addr] "m" (* (uint8_t *) addr)
        : "cc", "memory"
    );

    return status;
}

static inline bool test_and_reset_bit(unsigned int bit, volatile void *addr) {
    bool status;

    asm volatile (
        "lock btr %[bit], %[addr];"
        "setc %[status];"
        : [status] "=r" (status)
        : [bit] "Ir" (bit), [addr] "m" (* (uint8_t *) addr)
        : "cc", "memory"
    );

    return status;
}

static inline bool test_and_complement_bit(unsigned int bit, volatile void *addr) {
    bool status;

    asm volatile (
        "lock btc %[bit], %[addr];"
        "setc %[status];"
        : [status] "=r" (status)
        : [bit] "Ir" (bit), [addr] "m" (* (uint8_t *) addr)
        : "cc", "memory"
    );

    return status;
}

/* External declarations */

#endif /* KTF_ATOMIC_H */
