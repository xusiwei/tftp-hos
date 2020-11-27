/*
 * Copyright (c) 2020, HiHope Community.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef TFTP_LOG_H
#define TFTP_LOG_H

#include <stdio.h>

#define LOGI(fmt, ...) printf("[%s:%d %s] tftp INFO " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#ifndef NDEBUG
#define LOGD(fmt, ...) printf("[%s:%d %s] tftp DEBUG " fmt "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)

#define HEXDUMP(ptr, size) do { \
    LOGD("HEXDUMP(%s, %d): ", #ptr, size); \
    hexdump(ptr, size);  \
} while (0)

#ifdef LWIP_DEBUGF
#undef LWIP_DEBUGF
#define LWIP_DEBUGF(dbg, args) printf args
#endif

#else
#define LOGD(fmt, ...)
#define HEXDUMP(ptr, size)
#endif

void hexdump(void* ptr, int size);

#endif  // TFTP_LOG_H