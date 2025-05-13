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

#include <argp.h>
#include <errno.h>
#include <error.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "triple.h"

bool verbose = false;
bool unconcise = false;
bool printinfo = false;

static const struct argp_option argsoptions[] = {
    { NULL, 0, NULL, 0, "Host specification:", 1 },
    { "cpu", 'm', "ARCH", 0, "Specify a cpu instruction set architecture", 0 },
    { "system", 's', "SYSTEM", 0, "Specify a host system", 0 },

    { NULL, 0, NULL, 0, "Output:", 2 },
    { "verbose", 'v', NULL, 0, "Enable verbose output to stderr", 0 },
    { "full-target", 'T', NULL, 0, "Output full (unconcise) triple", 0 },
    { "info", 'i', NULL, 0, "Print additional info about triple to stderr", 0 },
    { 0 }
};

static int argsparse(int key, char *arg, struct argp_state *state) {
    switch(key) {
        case 'm':
            set_architecture(arg);
            break;
        case 's':
            set_system(arg);
            break;

        case 'v':
            verbose = true;
            break;
        case 'T':
            unconcise = true;
            break;
        case 'i':
            printinfo = true;
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }

    return 0;
}

static const struct argp argsinfo = {
    .options = argsoptions,
    .parser = argsparse,
};

int main(int argc, char **argv) {
    if(argp_parse(&argsinfo, argc, argv, 0, NULL, NULL) != 0) {
        error(errno, errno, "failed to parse arguments");
    }
    
    init_native_defaults();

    char triplestr[256] = "";

    append_architecture_str(triplestr);
    strcat(triplestr, "-");

    if(append_system_str(triplestr)) {
        strcat(triplestr, "-");
    }

    append_environment_str(triplestr);

    printf("%s\n", triplestr);
    return 0;
}

void printv(const char *fmt, ...) {
    if(!verbose) return;

    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);

    va_end(args);
}
