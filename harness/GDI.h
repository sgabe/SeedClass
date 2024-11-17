/*
 *   Copyright (c) 2024 Gabor Seljan. All rights reserved.
 *   Licensed under the MIT License.
 */

#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <shlwapi.h>
#include <inttypes.h>
#include <gdiplusgraphics.h>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "shlwapi.lib")

#define MAX_SAMPLE_SIZE 1000000

unsigned char* shm_data;
bool use_shared_memory;
HANDLE map_file;


int setup_shmem(LPCWSTR name)
{
    map_file = OpenFileMapping(
        FILE_MAP_ALL_ACCESS,
        FALSE,
        name
    );

    if (map_file == NULL)
    {
#if _DEBUG
        OutputDebugString(L"Error accessing shared memory");

        DWORD dLastError = GetLastError();
        LPCTSTR strErrorMessage = NULL;

        FormatMessage(
            FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
            NULL,
            dLastError,
            0,
            (LPWSTR)&strErrorMessage,
            0,
            NULL);

        OutputDebugString(strErrorMessage);
#endif
        return 0;
    }

    shm_data = (unsigned char*)MapViewOfFile(
        map_file,
        FILE_MAP_ALL_ACCESS,
        0,
        0,
        MAX_SAMPLE_SIZE + sizeof(uint32_t)
    );

    if (shm_data == NULL)
    {
#if _DEBUG
        OutputDebugString(L"Error accessing shared memory");
#endif
        return 0;
    }

    return 1;
}


int clear_shmem(void)
{
    UnmapViewOfFile(shm_data);
    CloseHandle(map_file);

    return 0;
}


LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
        return 0;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        EndPaint(hWnd, &ps);
    }
    return 0;
    }

    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
