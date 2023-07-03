#pragma once

#include <cstdint>
#include <cstdio>

// Set the base directory for file operations.
std::size_t pxwrFile_set_base_directory(const char* dir);

// Get file size.
bool pxwrFile_get_size(FILE* file, int* outSizeWrote);

// Open a file using the master directory.
FILE* pxwrFile_open_master(const char* dir, const char* file, const char* mode, int* outFileLen);

// Open a file using the resource directory.
FILE* pxwrFile_open_trns(const char* dir, const char* file, const char* mode, int* outFileLen);