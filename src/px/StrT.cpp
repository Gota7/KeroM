#include "px/StrT.hpp"

#include <cstring>
#include <cstdlib>

char* pxStrT_copy_allocate(const char* str)
{
    return pxStrT_copy_allocate(str, 0);
}

char* pxStrT_copy_allocate(const char* str, int extraLen)
{
    size_t len = strlen(str);
    size_t fullLen = len + 1 + extraLen;
    char* ret = (char*)malloc(fullLen);
    if (ret)
    {
        size_t extra = 0;
        if (fullLen >= len)
        {
            extra = fullLen - len;
        }
        bzero(ret + len, extra);
        memcpy(ret, str, len);
    }
    return ret;
}

bool pxStrT_copy(char* dest, const char* src)
{
    memcpy(dest, src, strlen(src) + 1);
    return true;
}

void pxStrT_free(char** str)
{
    if (*str)
    {
        free(*str);
        *str = nullptr;
    }
}

std::size_t pxStrT_size(const char* str)
{
    if (str)
        return strlen(str);
    else
        return 0;
}