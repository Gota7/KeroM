#pragma once

// Free the debug log.
void pxDebugLog_release();

// Initialize the debugger. Returns if successful.
bool pxDebugLog_init(const char* logDir);

// Log a string.
void dlog_c(const char* format, ...);