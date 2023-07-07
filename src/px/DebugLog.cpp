#include "px/DebugLog.hpp"

#include "px/DateTime.hpp"
#include "px/File.hpp"
#include "px/Mutex.hpp"
#include "px/StrT.hpp"
#include <cstdarg>
#include <cstring>

#define MAX_LOG_SIZE 0x400
#define MAX_LOG_FILENAME_LEN 0x20

#ifdef BUG_FIXES
// If the debug log has been initialized.
bool _b_init = false;
#else
// If the debug log has been initialized.
bool _b_init;
#endif

// Directory name for the log.
char* _dir_name;

// Mutex for ensuring only one thread has access at a time.
pxMutex* _mtx;

void pxDebugLog_release()
{
    _b_init = false;
    if (_mtx)
    {
        delete _mtx;
        _mtx = nullptr;
    }
    pxStrT_free(&_dir_name);
}

bool pxDebugLog_init(const char* logDir)
{
    if (_b_init) return false;

    // Allocate resources as needed.
    _dir_name = pxStrT_copy_allocate(logDir);
    if (_dir_name)
    {
        if (pxFile::sttc_create_trns_sub_dir(logDir))
        {
            _mtx = new pxMutex();
            if (_mtx->init())
            {
                _b_init = true;
                return true;
            }
        }
    }

    // Free resources as needed.
    pxDebugLog_release();
    return false;

}

void dlog_c(const char* format, ...)
{
    if (!_b_init || !_mtx) return;
    char msg[MAX_LOG_SIZE];
    char logFile[MAX_LOG_FILENAME_LEN];

    // Prepare file name and message.
    _mtx->lock();
    pxDATETIME dateTime;
    pxDateTime_get_now(&dateTime);
    bzero(msg, MAX_LOG_SIZE);
    bzero(logFile, MAX_LOG_FILENAME_LEN);
    sprintf(logFile, "%04d%02d%02d.%s\n", dateTime.year, dateTime.month, dateTime.day, "dbg");

    // Add message and end with newline. Also show it to console.
    va_list args;
    vsnprintf(msg, MAX_LOG_SIZE - sizeof(wchar_t), format, args);
    size_t msgLen = strlen(msg);
    *(wchar_t*)(msg + msgLen) = '\n';
    printf("%s", msg);

    // Print message to file.
    if (_dir_name)
    {
        pxFile file(false, false);
        if (file.open(_dir_name, logFile, "a+t"))
        {
            file.w_arg_asfile(
                "%02d%02d%02d,%s",
                dateTime.hour,
                dateTime.minute,
                dateTime.second,
                msg
            );
            file.close();
        }
    }
    _mtx->unlock();

}