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

enum env_type env = ENV_UNKNOWN;

static enum env_type check_glibc(const char *str) {
    if(strcmp(str, "glibc") == 0 || strcmp(str, "gnu") == 0) {
        return env = ENV_GNU;
    }
    return ENV_UNKNOWN;
}

enum env_type set_environment(const char *str) {
    env = ENV_UNKNOWN;

    if(str == NULL) { return env; }
    else if(check_glibc(str)) {}

    return env;
}

const char * get_environment_str() {
    if(env == ENV_UNKNOWN) {
        if(sys == SYS_LINUX) {
            env = ENV_GNU;
        } else if(sys == SYS_NONE) {
            env = ENV_ELF;
        }
    }

    switch(env) {
        case ENV_GNU:
            if(sys == SYS_LINUX) {
                return "gnu";
            }
            error(ENOTSUP, 0, "environment 'gnu/glibc' not supported for system '%s'", get_system_str());
        case ENV_ELF:
            return "elf";
        default:
    }
    error(ENOTSUP, 0, "unknown/unsupported environment type");
    __builtin_unreachable();
}
