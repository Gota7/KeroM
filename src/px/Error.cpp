#include "px/Error.hpp"

// If an error has been encountered.
#ifdef BUG_FIXES
bool _b_err = false;
#else
bool _b_err;
#endif

// Message that has been buffered.
char* _buf;

bool pxError_is_error()
{
    return _b_err;
}

char* pxError_get_message()
{
    return _buf;
}