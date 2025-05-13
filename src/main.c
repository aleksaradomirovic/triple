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
#include <stdio.h>

#include "triple.h"

static const struct argp_option argsoptions[] = {
    { "cpu", 'm', "ARCH", 0, "Specify a cpu instruction set architecture", 0 },
    { "system", 's', "SYSTEM", 0, "Specify a host system", 0 },
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
    init_native_defaults();

    if(argp_parse(&argsinfo, argc, argv, 0, NULL, NULL) != 0) {
        error(errno, errno, "failed to parse arguments");
    }

    printf("%s-%s-%s\n", get_architecture_str(), get_system_str(), get_environment_str());

    return 0;
}
