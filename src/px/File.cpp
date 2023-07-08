#include "px/File.hpp"

#include "pxwr/File.hpp"
#include <cstdarg>
#include <cstdlib>
#include <cstring>

#define TMP_BUF_LEN 0x400

pxFile::pxFile(bool noTrns, bool unused)
{
    this->unused = unused;
    this->noTrns = noTrns;
    file = nullptr;
    fileLen = 0;
    position = 0;
    isOpen = false;
    tmpBuf = nullptr;
    unk = nullptr;
    unkThing = 0;
}

bool pxFile::close()
{
    if (isOpen && file)
        fclose(file);
    file = nullptr;
    isOpen = false;
    fileLen = 0;
    position = 0;
    return true;
}

bool pxFile::sttc_set_master_base_dir(const char* dir)
{
    return pxwrFile_set_base_directory(dir);
}

bool pxFile::sttc_set_master_cmmn_dir(const char* dir)
{
    return pxwrFile_set_cmmn_directory(dir);
}

bool pxFile::sttc_set_trns_dir(const char* dir)
{
    return pxwrFile_set_trns_directory(dir);
}

bool pxFile::sttc_create_trns_sub_dir(const char* dir)
{
    return pxwrFile_create_trns_sub_dir(dir);
}

FILE* pxFile::get_file_descriptor()
{
    if (isOpen)
        return file;
    else
        return nullptr;
}

bool pxFile::get_position(int* outPos) const
{
    if (!file) return false;
    if (isOpen)
        *outPos = (int)ftell(file);
    else
        *outPos = position;
    return true;
}

bool pxFile::get_size_bytes(int* outSize) const
{
    if (!file) return false;
    *outSize = fileLen;
    return true;
}

bool pxFile::get_size_wrote(int* outSizeWrote) const
{
    if (file && isOpen)
        return pxwrFile_get_size(file, outSizeWrote);
    else
        return false;
}

bool pxFile::open(const char* dir, const char* file, const char* mode)
{
    if (isOpen && this->file) fclose(this->file);

    // Initialize file.
    fileLen = 0;
    if (this->noTrns)
        this->file = pxwrFile_open_master(dir, file, mode, &fileLen);
    else
        this->file = pxwrFile_open_trns(dir, file, mode, &fileLen);
    isOpen = this->file != nullptr;
    return isOpen;

}

bool pxFile::r(void* dest, int itemSize, int numItems)
{
    if (!file) return false;
    if (isOpen)
    {
        return fread(dest, itemSize, numItems, file) == (size_t)numItems;
    }
    else
    {
        if (numItems <= 0) return false;
        // TODO: MEMORY STREAMS!!!
    }
}

bool pxFile::w_arg_asfile(const char* format, ...)
{
    if (!file || !isOpen) return false;

    // Allocate buffer if non-existent.
    if (!tmpBuf)
    {
        tmpBuf = (char*)malloc(TMP_BUF_LEN);
        if (!tmpBuf) return false;
    }

    // Write data.
    bzero(tmpBuf, TMP_BUF_LEN);
    va_list args;
    va_start(args, format);
    vsprintf(tmpBuf, format, args);
    va_end(args);
    fwrite(tmpBuf, 1, strlen(tmpBuf), file);
    return true;

}

bool pxFile::w_asfile(const void* src, int itemSize, int numItems)
{
    if (file && isOpen)
        return fwrite(src, itemSize, numItems, file) == (size_t)numItems;
    else
        return false;
}