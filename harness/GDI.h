/*
 *   Copyright (c) 2026 Gabor Seljan. All rights reserved.
 *   Licensed under the MIT License.
 */

#pragma once

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include <vector>

#include <windows.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <gdiplus.h>
#include <gdiplusgraphics.h>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "user32.lib")

#define MAX_SAMPLE_SIZE 1000000u

extern unsigned char* shm_data;
extern bool use_shared_memory;
extern HANDLE map_file;
extern LPCWSTR input_path;

int setup_shmem(LPCWSTR name);
int clear_shmem(void);
