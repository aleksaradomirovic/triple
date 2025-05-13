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

enum cpu_version_type {
    CPU_VERSION_UNKNOWN = 0,
};

enum cpu_version_type_i386 {
    CPU_VERSION_I386 = 3,
    CPU_VERSION_I486 = 4,
    CPU_VERSION_I586 = 5,
    CPU_VERSION_I686 = 6,
};

enum cpu_version_type cpu_version;

static enum cpu_type check_x64(const char *str) {
    if(strcmp(str, "x86_64") == 0) {
        return cpu = CPU_X86_64;
    }
    return CPU_UNKNOWN;
}

static enum cpu_type check_i386(const char *str) {
    if(strcmp(str, "i686") == 0) {
        cpu_version = CPU_VERSION_I686;
        return cpu = CPU_I386;
    } else if(strcmp(str, "i586") == 0) {
        cpu_version = CPU_VERSION_I586;
        return cpu = CPU_I386;
    } else if(strcmp(str, "i486") == 0) {
        cpu_version = CPU_VERSION_I486;
        return cpu = CPU_I386;
    } else if(strcmp(str, "i386") == 0) {
        cpu_version = CPU_VERSION_I386;
        return cpu = CPU_I386;
    }
    return CPU_UNKNOWN;
}

enum cpu_type set_architecture(const char *str) {
    cpu = CPU_UNKNOWN;

    if(check_x64(str)) {}
    else if(check_i386(str)) {}

    return cpu;
}

const char * get_architecture_str() {
    switch(cpu) {
        case CPU_X86_64:
            return "x86_64";
        case CPU_I386:
            switch((enum cpu_version_type_i386) cpu_version) {
                case CPU_VERSION_I386:
                    return "i386";
                case CPU_VERSION_I486:
                    return "i486";
                case CPU_VERSION_I586:
                    return "i586";
                case CPU_VERSION_I686:
                    return "i686";
            }
            error(ENOTSUP, 0, "unknown/unsupported cpu version");
        default:
    }
    error(ENOTSUP, 0, "unknown/unsupported cpu type");
    __builtin_unreachable();
}

bool append_architecture_str(char *triplestr) {
    strcat(triplestr, get_architecture_str());
    return true;
}
