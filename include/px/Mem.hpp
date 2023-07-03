#pragma once

// Initialize memory as all zeroes.
bool pxMem_zero_alloc(void** dest, unsigned int len);

// Free memory.
bool pxMem_free(void** mem);

// Set memory to zero.
bool pxMem_zero(void* mem, unsigned int len);