/*
 *   Copyright (c) 2024 Gabor Seljan. All rights reserved.
 *   Licensed under the MIT License.
 */

#include "GDI.h"

using namespace Gdiplus;

extern "C" __declspec(noinline dllexport) int Fuzz(HDC hDC)
{
    int argCount;
    LPWSTR* szArgList;
    HENHMETAFILE hEmf = NULL;
    uint32_t sample_size = 0;
    char* sample_bytes = NULL;
    Gdiplus::Image* image = NULL;
    Gdiplus::Image* thumbnail = NULL;
    Gdiplus::Metafile* metafile = NULL;
    Gdiplus::Graphics* graphics = NULL;

    szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);

    if (!use_shared_memory)
    {
        IStream* stream;
        SHCreateStreamOnFile(szArgList[2], NULL, &stream);
        image = Gdiplus::Image::FromStream(stream);
        metafile = new Gdiplus::Metafile(stream, hDC);
    }
    else
    {
        if (shm_data == NULL)
        {
#if _DEBUG
            OutputDebugString(L"Failed to retrieve image data from shared memory");
#endif
            return 1;
        }

        sample_size = *(uint32_t*)(shm_data);
        if (sample_size > MAX_SAMPLE_SIZE) sample_size = MAX_SAMPLE_SIZE;
        sample_bytes = (char*)malloc(sample_size);
        if (sample_bytes == NULL)
        {
#if _DEBUG
            OutputDebugString(L"Insufficient memory available");
#endif
            return 1;
        }
        memcpy(sample_bytes, shm_data + sizeof(uint32_t), sample_size);
        IStream* stream = SHCreateMemStream(reinterpret_cast<BYTE*>(sample_bytes), sample_size);
        image = Gdiplus::Image::FromStream(stream);
        metafile = new Gdiplus::Metafile(stream, hDC);
    }

    if (image && (Ok == image->GetLastStatus()))
    {
#if _DEBUG
        OutputDebugString(L"Image loaded");
#endif
        thumbnail = image->GetThumbnailImage(100, 100, NULL, NULL);
        if (thumbnail && (Ok == thumbnail->GetLastStatus()))
        {
#if _DEBUG
            OutputDebugString(L"Thumbnail created");
#endif
        }

        graphics = Graphics::FromImage(image);
        if (graphics && (Ok == graphics->GetLastStatus()))
        {
#if _DEBUG
            OutputDebugString(L"Graphics created");
#endif
            graphics->DrawImage(image, 0, 0);
        }
    }

    if (metafile)
    {
#if _DEBUG
        OutputDebugString(L"Metafile loaded");
#endif
        hEmf = metafile->GetHENHMETAFILE();
        for (size_t x = 1; x <= 8; x++)
        {
            for (size_t y = 0; y <= 4; y++)
            {
#if _DEBUG
                OutputDebugString(L"Metafile converted");
#endif
                Gdiplus::Metafile::EmfToWmfBits(hEmf, 0, NULL, (INT)x, (INT)y);
            }
        }
    }

    if (image) delete image;
    if (metafile) delete metafile;
    if (thumbnail) delete thumbnail;
    if (graphics) delete graphics;
    if (sample_bytes) free(sample_bytes);
    if (hEmf) DeleteEnhMetaFile(hEmf);

    LocalFree(szArgList);

    return 0;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int argCount;
    LPWSTR* szArgList;
    ULONG_PTR gdiplusToken;
    GdiplusStartupInput gdiplusStartupInput;

    GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);
    if (szArgList == NULL || argCount < 3)
    {
#if _DEBUG
        OutputDebugString(L"Not enough parameters");
#endif
        return 1;
    }

    if (!wcscmp(szArgList[1], L"-s"))
    {
#if _DEBUG
        OutputDebugString(L"Running in shared memory mode");
#endif
        use_shared_memory = true;
    }
    else if (!wcscmp(szArgList[1], L"-f"))
    {
#if _DEBUG
        OutputDebugString(L"Running in file mode");
#endif
        use_shared_memory = false;
    }
    else
    {
#if _DEBUG
        OutputDebugString(L"Wrong parameters");
#endif
        return 0;
    }

    if (use_shared_memory)
    {
        if (!setup_shmem(szArgList[2]))
        {
#if _DEBUG
            OutputDebugString(L"Error mapping shared memory");
#endif
            return 1;
        }
    }

    HDC hDC = GetDC(NULL);

    Fuzz(hDC);

    if (use_shared_memory) clear_shmem();
    ReleaseDC(NULL, hDC);
    LocalFree(szArgList);
    GdiplusShutdown(gdiplusToken);

    return 0;
}
