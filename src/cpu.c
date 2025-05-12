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

enum cpu_type cpu = CPU_UNKNOWN;

static enum cpu_type check_x64(const char *str) {
    if(strcmp(str, "x86_64") == 0) {
        return cpu = CPU_X86_64;
    }
    return CPU_UNKNOWN;
}

enum cpu_type set_architecture(const char *str) {
    cpu = CPU_UNKNOWN;

    if(check_x64(str)) {}

    return cpu;
}

const char * get_architecture_str() {
    switch(cpu) {
        case CPU_X86_64:
            return "x86_64";
        default:
            error(ENOTSUP, 0, "unknown/unsupported cpu type");
    }
    __builtin_unreachable();
}
