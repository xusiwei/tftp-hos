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
#ifndef TFTP_FS_H
#define TFTP_FS_H

#include "lwip/apps/tftp_server.h"

/**
 * Open file for read/write.
 * @param fname Filename
 * @param mode Mode string from TFTP RFC 1350 (netascii, octet, mail)
 * @param write Flag indicating read (0) or write (!= 0) access
 * @returns File handle supplied to other functions
 */
void* tftp_fs_open(const char* fname, const char* mode, u8_t write);

/**
 * Close file handle
 * @param handle File handle returned by open()
 */
void tftp_fs_close(void* handle);

/**
 * Read from file 
 * @param handle File handle returned by open()
 * @param buf Target buffer to copy read data to
 * @param bytes Number of bytes to copy to buf
 * @returns &gt;= 0: Success; &lt; 0: Error
 */
int tftp_fs_read(void* handle, void* buf, int bytes);

/**
 * Write to file
 * @param handle File handle returned by open()
 * @param pbuf PBUF adjusted such that payload pointer points
 *             to the beginning of write data. In other words,
 *             TFTP headers are stripped off.
 * @returns &gt;= 0: Success; &lt; 0: Error
 */
int tftp_fs_write(void* handle, struct pbuf* p);

#endif  // TFTP_FS_H