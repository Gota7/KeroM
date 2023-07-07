#include "px/File.hpp"

#include "pxwr/File.hpp"
#include <cstring>

pxFile::pxFile(bool noTrns, bool unused)
{
    this->unused = unused;
    this->noTrns = noTrns;
    file = nullptr;
    fileLen = 0;
    position = 0;
    isOpen = false;
    bzero(unkPath, 0x10);
    unkThing = 0;
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

bool pxFile::w_asfile(const void* src, int itemSize, int numItems)
{
    if (file && isOpen)
        return fwrite(src, itemSize, numItems, file) == (size_t)numItems;
    else
        return false;
}