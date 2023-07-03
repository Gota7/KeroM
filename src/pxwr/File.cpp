#include "pxwr/File.hpp"

#include "pxw/File.hpp"

std::size_t pxwrFile_set_base_directory(const char* dir)
{
    return pxwFile_set_master_base_dir(dir);
}

bool pxwrFile_get_size(FILE* file, int* outSizeWrote)
{
    if (!file || !outSizeWrote) return false;
    long bakPos = ftell(file);
    fseek(file, 0, SEEK_END);
    *outSizeWrote = (int)ftell(file);
    fseek(file, bakPos, SEEK_SET);
    return true;
}

FILE* pxwrFile_open_master(const char* dir, const char* file, const char* mode, int* outFileLen)
{
    char realPath[0x110];
    if (!pxwFile_get_real_path_master_base(realPath, dir, file)) return nullptr;

    // Correct path if needed.
    FILE* filePtr = fopen(realPath, mode);
    if (!filePtr)
    {
        if (!pxwFile_get_real_path_master_cmmn(realPath, dir, file)) return nullptr;
        filePtr = fopen(realPath, mode);
        if (!filePtr) return nullptr;
    }

    // Get file length.
    if (mode[0] != 'w' && outFileLen)
    {
        fseek(filePtr, 0, SEEK_END);
        *outFileLen = (int)ftell(filePtr);
        fseek(filePtr, 0, SEEK_SET);
    }
    return filePtr;

}

FILE* pxwrFile_open_trns(const char* dir, const char* file, const char* mode, int* outFileLen)
{
    char realPath[0x110];
    if (!pxwFile_get_real_path_trns(realPath, dir, file)) return nullptr;

    // Get file length.
    FILE* filePtr = fopen(realPath, mode);
    if (!filePtr) return nullptr;
    if (mode[0] != 'w' && outFileLen)
    {
        fseek(filePtr, 0, SEEK_END);
        *outFileLen = (int)ftell(filePtr);
        fseek(filePtr, 0, SEEK_SET);
    }
    return filePtr;

}