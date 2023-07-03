#pragma once

#include <stdbool.h>

// If an error has been recorded for px system.
bool pxError_is_error(void);

// Get the bufferred error message.
char* pxError_get_message(void);