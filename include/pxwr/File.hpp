#pragma once

#include <cstdint>
#include <cstdio>

// Set the base directory for file operations.
bool pxwrFile_set_base_directory(const char* dir);

// Set the common directory for file operations.
bool pxwrFile_set_cmmn_directory(const char* dir);

// Set the resource directory for file operations.
bool pxwrFile_set_trns_directory(const char* dir);

// Create a sub-directory in the resource path.
bool pxwrFile_create_trns_sub_dir(const char* dir);

// Get file size.
bool pxwrFile_get_size(FILE* file, int* outSizeWrote);

// Open a file using the master directory.
FILE* pxwrFile_open_master(const char* dir, const char* file, const char* mode, int* outFileLen);

// Open a file using the resource directory.
FILE* pxwrFile_open_trns(const char* dir, const char* file, const char* mode, int* outFileLen);