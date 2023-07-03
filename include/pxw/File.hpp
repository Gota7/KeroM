#pragma once

#include <cstdint>

// Set the base directory for file operations.
std::size_t pxwFile_set_master_base_dir(const char* dir);

// Create a directory in resource path.
bool pxwFile_create_trns_sub_dir(const char* dir);

// Get the true path from a base path.
bool pxwFile_get_real_path_master_base(char* outRealPath, const char* dir, const char* file);

// Get the true path from a common path.
bool pxwFile_get_real_path_master_cmmn(char* outRealPath, const char* dir, const char* file);

// Get the true path from a resource path.
bool pxwFile_get_real_path_trns(char* outRealPath, const char* dir, const char* file);