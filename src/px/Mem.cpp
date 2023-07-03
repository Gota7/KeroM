#include "px/Mem.hpp"

#include <cstdlib>
#include <cstring>

bool pxMem_zero_alloc(void** dest, unsigned int len)
{
    *dest = calloc(1, len);
    return *dest;
}

bool pxMem_free(void** mem)
{
    if (mem && *mem)
    {
        free(*mem);
        *mem = nullptr;
        return true;
    }
    else return false;
}

bool pxMem_zero(void* mem, unsigned int len)
{
    if (mem && len)
        bzero(mem, len);
    return mem;
}