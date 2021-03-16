/*
 * Copyright 2020 Arduino SA
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @file
 *  Provides wiced fs porting to generic mbed APIs
 */

#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include "sockets.h"
#include "wiced_filesystem.h"

static bool filesystem_mounted = false;
extern bool wiced_filesystem_mount();

wiced_result_t wiced_filesystem_file_open(wiced_filesystem_t *fs_handle, wiced_file_t *file_handle_out, const char *filename, wiced_filesystem_open_mode_t mode)
{
    if (!filesystem_mounted) {
        filesystem_mounted = wiced_filesystem_mount();
    }
    if (!filesystem_mounted) {
        return WICED_ERROR;
    }
    *file_handle_out = open(filename, O_RDONLY);
    if (*file_handle_out == -1) {
        return WICED_ERROR;
    }
    return WICED_SUCCESS;
}

wiced_result_t wiced_filesystem_file_seek(wiced_file_t *file_handle, int64_t offset, wiced_filesystem_seek_type_t whence)
{
    if (*file_handle == -1) {
        return WICED_ERROR;
    }
    lseek(*file_handle, offset, whence);
    return WICED_SUCCESS;
}

wiced_result_t wiced_filesystem_file_read(wiced_file_t *file_handle, void *data, uint64_t bytes_to_read, uint64_t *returned_bytes_count)
{
    if (*file_handle == -1) {
        return WICED_ERROR;
    }
    *returned_bytes_count = read(*file_handle, data, bytes_to_read);
    return WICED_SUCCESS;
}

wiced_result_t wiced_filesystem_file_close(wiced_file_t *file_handle)
{
    if (*file_handle == -1) {
        return WICED_ERROR;
    }
    close(*file_handle);
    return WICED_SUCCESS;
}
