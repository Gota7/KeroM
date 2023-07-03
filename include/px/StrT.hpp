#pragma once

#include <cstdint>

// Make a new string from an existing one.
char* pxStrT_copy_allocate(const char* str);

// Make a new string from an existing one and save room for more info after.
char* pxStrT_copy_allocate(const char* str, int extraLen);

// Copy a string from source to destination.
bool pxStrT_copy(char* dest, const char* src);

// Free a string. Will only do it if string is not null.
void pxStrT_free(char** str);

// Get the size of a string.
std::size_t pxStrT_size(const char* str);