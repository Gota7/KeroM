#include "px/DateTime.hpp"

tm pxDateTime_get_time(const pxDATETIME* t)
{
    tm ret;
    ret.tm_year = t->year - 1900;
    ret.tm_mon = t->month - 1;
    ret.tm_mday = t->day;
    ret.tm_hour = 0;
    ret.tm_min = 0;
    ret.tm_sec = 0;
    return ret;
}

int pxDateTime_compare_seconds(const pxDATETIME* t1, const pxDATETIME* t2)
{
    tm tm1 = pxDateTime_get_time(t1);
    tm tm2 = pxDateTime_get_time(t2);
    return difftime(mktime(&tm1), mktime(&tm2));
}

bool pxDateTime_get_now(pxDATETIME* outDateTime)
{
    time_t timeT;
    time(&timeT);
    tm* localtimeT = localtime(&timeT);
    outDateTime->year = localtimeT->tm_year + 1900;
    outDateTime->month = localtimeT->tm_mon + 1;
    outDateTime->day = localtimeT->tm_mday;
    outDateTime->hour = localtimeT->tm_hour;
    outDateTime->minute = localtimeT->tm_min;
    outDateTime->second = localtimeT->tm_sec;
}