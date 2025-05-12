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

int init_native_defaults() {
    struct utsname sysinfo;
    if(uname(&sysinfo) != 0) {
        error(errno, errno, "failed to get native system information");
    }

    to_lower_str(sysinfo.sysname, sizeof(sysinfo.sysname));
    to_lower_str(sysinfo.machine, sizeof(sysinfo.machine));

    set_architecture(sysinfo.machine);
    set_system(sysinfo.sysname);
    set_environment(NULL);

    return 0;
}
