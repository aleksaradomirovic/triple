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

#pragma once

// cpu, system, environment

enum cpu_type {
    CPU_UNKNOWN = 0,
    CPU_X86_64,
    CPU_I386,
};

extern enum cpu_type cpu;

enum cpu_type set_architecture(const char *str);
const char * get_architecture_str();

enum sys_type {
    SYS_UNKNOWN = 0,
    SYS_NONE,
    SYS_LINUX,
};

extern enum sys_type sys;

enum sys_type set_system(const char *str);
const char * get_system_str();

enum env_type {
    ENV_UNKNOWN = 0,
    ENV_ELF,
    ENV_GNU,
};

extern enum env_type env;

enum env_type set_environment(const char *str);
const char * get_environment_str();

int init_native_defaults();
