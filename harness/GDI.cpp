/*
 *   Copyright (c) 2026 Gabor Seljan. All rights reserved.
 *   Licensed under the MIT License.
 */

#include "GDI.h"

using namespace Gdiplus;

#if _DEBUG
#define LOG(msg) do { OutputDebugStringW(msg); } while (0)
#else
#define LOG(msg) do {} while (0)
#endif

static UINT GetMaxDerivedEmfBits()
{
    if (MAX_SAMPLE_SIZE > (UINT_MAX / 4))
        return UINT_MAX;
    return MAX_SAMPLE_SIZE * 4;
}

static int CALLBACK EmfEnumProc(
    HDC dc,
    HANDLETABLE* ht,
    const ENHMETARECORD* rec,
    int n,
    LPARAM lp)
{
    return PlayEnhMetaFileRecord(dc, ht, rec, n);
}

extern "C" __declspec(noinline dllexport) int Fuzz(HDC hDC)
{
    int argCount;
    LPWSTR* szArgList;
    HENHMETAFILE hEmf = NULL;
    uint32_t sample_size = 0;
    char* sample_bytes = NULL;

    IStream* stream = NULL;
    Gdiplus::Image* image = NULL;
    Gdiplus::Image* thumbnail = NULL;
    Gdiplus::Metafile* metafile = NULL;
    Gdiplus::Graphics* graphics = NULL;

    szArgList = CommandLineToArgvW(GetCommandLine(), &argCount);

    if (!use_shared_memory)
    {
        SHCreateStreamOnFile(szArgList[2], NULL, &stream);
        image = Gdiplus::Image::FromStream(stream);
        metafile = new Gdiplus::Metafile(stream, hDC);
    }
    else
    {
        if (shm_data == NULL)
        {
            LOG(L"Failed to retrieve image data from shared memory");
            return 1;
        }

        sample_size = *(uint32_t*)(shm_data);
        if (sample_size > MAX_SAMPLE_SIZE) sample_size = MAX_SAMPLE_SIZE;
        sample_bytes = (char*)malloc(sample_size);
        if (sample_bytes == NULL)
        {
            LOG(L"Insufficient memory available");
            return 1;
        }
        memcpy(sample_bytes, shm_data + sizeof(uint32_t), sample_size);
        stream = SHCreateMemStream(reinterpret_cast<BYTE*>(sample_bytes), sample_size);
        image = Gdiplus::Image::FromStream(stream);
        metafile = new Gdiplus::Metafile(stream, hDC);
    }

    if (image && (Ok == image->GetLastStatus()))
    {
        LOG(L"Image loaded");
        thumbnail = image->GetThumbnailImage(100, 100, NULL, NULL);
        if (thumbnail && (Ok == thumbnail->GetLastStatus()))
        {
            LOG(L"Thumbnail created");
        }

        graphics = Graphics::FromImage(image);
        if (graphics && (Ok == graphics->GetLastStatus()))
        {
            LOG(L"Graphics created from image");
            graphics->DrawImage(image, 0, 0);
        }

        if (graphics)
        {
            delete graphics;
            graphics = NULL;
        }

        graphics = Graphics::FromImage(metafile);
        if (graphics && (Ok == graphics->GetLastStatus()))
        {
            LOG(L"Graphics created from metafile");
            graphics->DrawImage(image, 0, 0);
        }
    }

    if (metafile)
    {
        LOG(L"Metafile loaded");
        RECT rcZero = { 0, 0, 0, 0 };
        RECT rcSmall = { 0, 0, 1, 1 };
        RECT rcNormal = { 0, 0, 512, 512 };
        hEmf = metafile->GetHENHMETAFILE();

        LOG(L"Metafile played");

        PlayEnhMetaFile(hDC, hEmf, &rcZero);
        PlayEnhMetaFile(hDC, hEmf, &rcSmall);
        PlayEnhMetaFile(hDC, hEmf, &rcNormal);

        LOG(L"Metafile enumerated");

        EnumEnhMetaFile(hDC, hEmf, EmfEnumProc, NULL, &rcZero);
        EnumEnhMetaFile(hDC, hEmf, EmfEnumProc, NULL, &rcSmall);
        EnumEnhMetaFile(hDC, hEmf, EmfEnumProc, NULL, &rcNormal);

        UINT sz = GetEnhMetaFileBits(hEmf, 0, NULL);
        if (sz && sz <= GetMaxDerivedEmfBits())
        {
            LOG(L"Metafile size retrieved");
            std::vector<BYTE> buf(sz);
            if (GetEnhMetaFileBits(hEmf, sz, buf.data()))
            {
                LOG(L"Metafile bits extracted");
                HENHMETAFILE h2 = SetEnhMetaFileBits(sz, buf.data());
                if (h2)
                {
                    LOG(L"Metafile reconstructed");
                    PlayEnhMetaFile(hDC, h2, &rcZero);
                    PlayEnhMetaFile(hDC, h2, &rcSmall);
                    PlayEnhMetaFile(hDC, h2, &rcNormal);
                    DeleteEnhMetaFile(h2);
                }
            }
        }

        for (size_t x = 1; x <= 8; x++)
        {
            for (size_t y = 0; y <= 4; y++)
            {
                LOG(L"Metafile converted");
                Gdiplus::Metafile::EmfToWmfBits(hEmf, 0, NULL, (INT)x, (INT)y);
            }
        }
    }

    if (graphics && metafile && metafile->GetLastStatus() == Ok)
    {
        LOG(L"Metafile drawn on image");
        graphics->DrawImage(metafile, 0, 0);
        graphics->DrawImage(metafile, Rect(0, 0, 100, 100));
    }

    if (image) delete image;
    if (metafile) delete metafile;
    if (thumbnail) delete thumbnail;
    if (graphics) delete graphics;
    if (sample_bytes) free(sample_bytes);
    if (hEmf) DeleteEnhMetaFile(hEmf);
    if (stream) stream->Release();

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
        LOG(L"Not enough parameters");
        return 1;
    }

    if (!wcscmp(szArgList[1], L"-s"))
    {
        LOG(L"Running in shared memory mode");
        use_shared_memory = true;
    }
    else if (!wcscmp(szArgList[1], L"-f"))
    {
        LOG(L"Running in file mode");
        use_shared_memory = false;
    }
    else
    {
        LOG(L"Wrong parameters");
        return 0;
    }

    if (use_shared_memory)
    {
        if (!setup_shmem(szArgList[2]))
        {
            LOG(L"Error mapping shared memory");
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
