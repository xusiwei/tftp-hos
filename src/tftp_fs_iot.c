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

#include "tftp_fs.h"
#include "utils_file.h" // OHOS IoT fs API 

#include <stdio.h>
#define LOGI(fmt, ...) printf("[%s:%d %s] tftp INFO " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#ifndef NDEBUG
#define LOGD(fmt, ...) printf("[%s:%d %s] tftp DEBUG " fmt "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define LOGD(fmt, ...)
#endif

/**
 * Open file for read/write.
 * @param fname Filename
 * @param mode Mode string from TFTP RFC 1350 (netascii, octet, mail)
 * @param write Flag indicating read (0) or write (!= 0) access
 * @returns File handle supplied to other functions
 */
void* tftp_fs_open(const char* fname, const char* mode, u8_t write)
{
    LOGD("fname: %s, mode: %s, write: %d", fname, mode, write);
    if (fname == NULL || mode == NULL) {
        LOGI("invalid args!");
        return NULL;
    }

    int oflag = 0;
    if (write) {
        oflag = O_RDWR_FS | O_CREAT_FS;
    }
    int fd = UtilsFileOpen(fname, oflag, 0);
    if (fd < 0) {
        LOGI("UtilsFileOpen failed!");
        return NULL;
    }
    LOGD("open %s success, fd = %d", fname, fd);
    return (void*) fd;
}

/**
 * Close file handle
 * @param handle File handle returned by open()
 */
void tftp_fs_close(void* handle)
{
    LOGD("handle: %p", handle);
    if (handle == NULL) {
        LOGI("invalid args!");
        return;
    }

    int fd = (int) handle;
    int ret = UtilsFileClose(fd);
    if (ret < 0) {
        LOGI("UtilsFileClose failed!");
    }
    LOGI("close %d success!", fd);
}

/**
 * Read from file 
 * @param handle File handle returned by open()
 * @param buf Target buffer to copy read data to
 * @param bytes Number of bytes to copy to buf
 * @returns &gt;= 0: Success; &lt; 0: Error
 */
int tftp_fs_read(void* handle, void* buf, int bytes)
{
    LOGD("handle: %p, buf: %p, bytes: %d", handle, buf, bytes);
    if (handle == NULL || buf == NULL) {
        LOGI("invalid args!");
        return -1;
    }

    int fd = (int) handle;
    int ret = UtilsFileRead(fd, buf, bytes);
    if (ret < 0) {
        LOGI("UtilsFileRead failed!");
        return ret;
    }
    LOGD("read %d bytes on fd %d success!", bytes, fd);
    return 0;
}

/**
 * Write to file
 * @param handle File handle returned by open()
 * @param pbuf PBUF adjusted such that payload pointer points
 *             to the beginning of write data. In other words,
 *             TFTP headers are stripped off.
 * @returns &gt;= 0: Success; &lt; 0: Error
 */
int tftp_fs_write(void* handle, struct pbuf* p)
{
    LOGD("handle: %p, p: %p", handle, p);
    if (handle == NULL || p == NULL) {
        LOGI("invalid args");
        return -1;
    }

    int fd = (int) handle;
    for (; p; p = p->next) {
        int ret = UtilsFileWrite(fd, p->payload, p->len);
        if (ret < 0) {
            LOGI("UtilsFileWrite failed!");
            return ret;
        }
        LOGD("write %d bytes on fd %d success!", p->len, p->payload);
    }
    return 0;
}
