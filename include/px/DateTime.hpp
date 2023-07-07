#pragma once

#include <cstdint>
#include <ctime>

// Date and time structure.
struct pxDATETIME
{
    int16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
};

// Make a time structure from a date time.
tm pxDateTime_get_time(const pxDATETIME* t);

// Compare the difference in time in seconds.
int pxDateTime_compare_seconds(const pxDATETIME* t1, const pxDATETIME* t2);

// Get the current date and time.
bool pxDateTime_get_now(pxDATETIME* outDateTime);