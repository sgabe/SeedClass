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

unsigned char* shm_data = NULL;
bool use_shared_memory = false;
HANDLE map_file = NULL;
LPCWSTR input_path = NULL;

int setup_shmem(LPCWSTR name)
{
    if (name == NULL)
    {
        LOG(L"Invalid shared memory name");
        return 0;
    }

    clear_shmem();

    map_file = OpenFileMappingW(
        FILE_MAP_READ,
        FALSE,
        name);

    if (map_file == NULL)
    {
        LOG(L"Error opening shared memory mapping");
        return 0;
    }

    shm_data = static_cast<unsigned char*>(
        MapViewOfFile(
            map_file,
            FILE_MAP_READ,
            0,
            0,
            MAX_SAMPLE_SIZE + sizeof(uint32_t)));

    if (shm_data == NULL)
    {
        LOG(L"Error mapping shared memory view");

        CloseHandle(map_file);
        map_file = NULL;

        return 0;
    }

    return 1;
}

int clear_shmem(void)
{
    if (shm_data)
    {
        UnmapViewOfFile(shm_data);
        shm_data = NULL;
    }

    if (map_file)
    {
        CloseHandle(map_file);
        map_file = NULL;
    }

    return 0;
}

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
    int ret = 0;
    HENHMETAFILE hEmf = NULL;
    uint32_t sample_size = 0;

    IStream* stream = NULL;
    Gdiplus::Image* image = NULL;
    Gdiplus::Image* thumbnail = NULL;
    Gdiplus::Metafile* metafile = NULL;
    Gdiplus::Graphics* graphics = NULL;

    if (!use_shared_memory)
    {
        HRESULT hr = SHCreateStreamOnFileW(
            input_path,
            STGM_READ | STGM_SHARE_DENY_NONE,
            &stream);

        if (FAILED(hr) || stream == NULL)
        {
            LOG(L"Failed to create file stream");
            ret = 1;
            goto cleanup;
        }

        image = Gdiplus::Image::FromStream(stream);

        LARGE_INTEGER zero = {};
        if (SUCCEEDED(stream->Seek(zero, STREAM_SEEK_SET, NULL)))
        {
            metafile = new Gdiplus::Metafile(stream);
        }
    }
    else
    {
        if (shm_data == NULL)
        {
            LOG(L"Failed to retrieve image data from shared memory");
            ret = 1;
            goto cleanup;
        }

        uint32_t raw_sample_size = 0;
        memcpy(&raw_sample_size, shm_data, sizeof(raw_sample_size));

        sample_size = raw_sample_size;
        if (sample_size > MAX_SAMPLE_SIZE)
            sample_size = MAX_SAMPLE_SIZE;

        const BYTE* sample_data = NULL;
        if (sample_size != 0)
            sample_data = reinterpret_cast<const BYTE*>(shm_data) + sizeof(uint32_t);

        stream = SHCreateMemStream(sample_data, sample_size);

        if (stream == NULL)
        {
            LOG(L"Failed to create memory stream");
            ret = 1;
            goto cleanup;
        }

        image = Gdiplus::Image::FromStream(stream);

        LARGE_INTEGER zero = {};
        if (SUCCEEDED(stream->Seek(zero, STREAM_SEEK_SET, NULL)))
        {
            metafile = new Gdiplus::Metafile(stream);
        }
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

        if (metafile)
        {
            graphics = Graphics::FromImage(metafile);

            if (graphics && graphics->GetLastStatus() == Ok)
            {
                LOG(L"Graphics created from metafile");
                graphics->DrawImage(image, 0, 0);
            }
        }
    }

    if (metafile && metafile->GetLastStatus() == Ok)
    {
        LOG(L"Metafile loaded");
        RECT rcZero = { 0, 0, 0, 0 };
        RECT rcSmall = { 0, 0, 1, 1 };
        RECT rcNormal = { 0, 0, 512, 512 };

        hEmf = metafile->GetHENHMETAFILE();

        if (hDC && hEmf)
        {
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
    }

    if (graphics && metafile && metafile->GetLastStatus() == Ok)
    {
        LOG(L"Metafile drawn on image");
        graphics->DrawImage(metafile, 0, 0);
        graphics->DrawImage(metafile, Rect(0, 0, 100, 100));
    }

cleanup:
    if (graphics) delete graphics;
    if (thumbnail) delete thumbnail;
    if (image) delete image;
    if (metafile) delete metafile;
    if (hEmf) DeleteEnhMetaFile(hEmf);
    if (stream) stream->Release();

    return ret;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int ret = 1;
    int argCount = 0;
    LPWSTR* szArgList = NULL;
    ULONG_PTR gdiplusToken = 0;
    bool gdiplusStarted = false;
    bool shmemMapped = false;
    HDC hDC = NULL;
    GdiplusStartupInput gdiplusStartupInput;

    if (GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL) != Ok)
    {
        LOG(L"GdiplusStartup failed");
        goto cleanup;
    }

    gdiplusStarted = true;

    szArgList = CommandLineToArgvW(GetCommandLineW(), &argCount);
    if (szArgList == NULL || argCount < 3)
    {
        LOG(L"Not enough parameters");
        goto cleanup;
    }

    input_path = szArgList[2];

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
        goto cleanup;
    }

    if (use_shared_memory)
    {
        if (!setup_shmem(szArgList[2]))
        {
            LOG(L"Error mapping shared memory");
            goto cleanup;
        }

        shmemMapped = true;
    }

    hDC = GetDC(NULL);

    ret = Fuzz(hDC);

cleanup:
    if (shmemMapped) clear_shmem();
    if (hDC) ReleaseDC(NULL, hDC);
    if (szArgList) LocalFree(szArgList);
    if (gdiplusStarted) GdiplusShutdown(gdiplusToken);

    return ret;
}
