#pragma once

#include <cstdint>
#include <cstdio>

#define FILE_ITEM_READ(file, item) file.r(&item, sizeof(item), 1)
#define FILE_ITEMS_READ(file, items, cnt) file.r(items, sizeof(*items), cnt)
#define FILE_ITEM_WRITE(file, item) file.w_asfile(&item, sizeof(item), 1)
#define FILE_ITEMS_WRITE(file, items, cnt) file.w_asfile(items, sizeof(*items), cnt)

// For file related activities.
class pxFile
{
    bool noTrns;
    bool unused;
    FILE* file;
    bool isOpen;
    int fileLen;
    int position;
    char* tmpBuf;
    char* unk;
    int unkThing;

public:

    // Make a new file reader/writer.
    pxFile(bool noTrns, bool unused);

    // Close the file.
    bool close();

    // Set the base directory to have paths be relative to.
    static bool sttc_set_master_base_dir(const char* dir);

    // Set the common directory.
    static bool sttc_set_master_cmmn_dir(const char* dir);

    // Set the resource directory.
    static bool sttc_set_trns_dir(const char* dir);

    // Create a sub-directory for resources.
    static bool sttc_create_trns_sub_dir(const char* dir);

    // Get the internal file descriptor.
    FILE* get_file_descriptor();

    // Get the current position of the file.
    bool get_position(int* outPos) const;

    // Get how many bytes are in the file
    bool get_size_bytes(int* outSize) const;

    // Get how many bytes have been wrote so far.
    bool get_size_wrote(int* outSizeWrote) const;

    // Open a file.
    bool open(const char* dir, const char* file, const char* mode);

    // Read items into a destination.
    bool r(void* dest, int itemSize, int numItems);

    // Write a variadic string to the file.
    bool w_arg_asfile(const char* format, ...);

    // Write items to a file.
    bool w_asfile(const void* src, int itemSize, int numItems);

};