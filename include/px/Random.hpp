#pragma once

// For random number generation.
class pxRandom
{
    unsigned short curr;
    unsigned short prev;

public:

    // Reset the number.
    void Reset();

    // New random number generator.
    pxRandom();

    // Seed RNG.
    void Set(unsigned short curr, unsigned short prev);

    // Get a new random number from [0, max).
    unsigned short Get(unsigned short max);

};