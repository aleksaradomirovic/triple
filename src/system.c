/*
 * Copyright 2025 Aleksa Radomirovic
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

#include "triple.h"

#include <errno.h>
#include <error.h>
#include <string.h>

enum sys_type sys = SYS_UNKNOWN;

static enum sys_type check_linux(const char *str) {
    if(strcmp(str, "linux") == 0) {
        return sys = SYS_LINUX;
    }
    return SYS_UNKNOWN;
}

static enum sys_type check_none(const char *str) {
    if(strcmp(str, "none") == 0 || strcmp(str, "freestanding") == 0) {
        return sys = SYS_NONE;
    }
    return SYS_UNKNOWN;
}

enum sys_type set_system(const char *str) {
    sys = SYS_UNKNOWN;

    if(check_linux(str)) {}
    else if(check_none(str)) {}

    return sys;
}

const char * get_system_str() {
    switch(sys) {
        case SYS_LINUX:
            return "linux";
        case SYS_NONE:
            return "none";
        default:
    }
    error(ENOTSUP, 0, "unknown/unsupported system type");
    __builtin_unreachable();
}
