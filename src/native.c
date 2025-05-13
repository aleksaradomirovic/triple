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

#include <ctype.h>
#include <errno.h>
#include <error.h>
#include <stddef.h>
#include <sys/utsname.h>

static void to_lower_str(char *str, size_t len) {
    for(size_t i = 0; i < len; i++) {
        str[i] = tolower(str[i]);
    }
}

#if defined(__x86_64__)
#   define NATIVE_CPU "x86_64"
#elif defined(__i686__)
#   define NATIVE_CPU "i686"
#elif defined(__i586__)
#   define NATIVE_CPU "i586"
#elif defined(__i486__)
#   define NATIVE_CPU "i486"
#elif defined(__i386__)
#   define NATIVE_CPU "i386"
#else
#   define NATIVE_CPU ""
#endif

int init_native_defaults() {
    struct utsname sysinfo;
    if(uname(&sysinfo) != 0) {
        error(errno, errno, "failed to get native system information");
    }

    to_lower_str(sysinfo.sysname, sizeof(sysinfo.sysname));
    // to_lower_str(sysinfo.machine, sizeof(sysinfo.machine));

    if(cpu == CPU_UNKNOWN) {
        set_architecture(NATIVE_CPU);
        if(cpu != CPU_UNKNOWN) {
            printv("deduced native cpu instruction set architecture as %s\n", get_architecture_str());
        } else {
            printv("failed to deduce native cpu instruction set architecture\n");
        }
    }

    if(sys == SYS_UNKNOWN) {
        set_system(sysinfo.sysname);
        if(sys != SYS_UNKNOWN) {
            printv("deduced native system as %s\n", get_system_str());
        } else {
            printv("failed to deduce native system\n");
        }
    }

    if(env == ENV_UNKNOWN) {
        set_environment(NULL);
        if(env != ENV_UNKNOWN) {
            printv("deduced native environment as %s\n", get_environment_str());
        } else {
            printv("failed to deduce native environment\n");
        }
    }

    return 0;
}
