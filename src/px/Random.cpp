#include "px/Random.hpp"

void pxRandom::Reset()
{
    curr = 0x1145;
    prev = 0x3811;
}

pxRandom::pxRandom()
{
    Reset();
}

void pxRandom::Set(unsigned short curr, unsigned short prev)
{
    this->curr = curr;
    this->prev = prev;
}

unsigned short pxRandom::Get(unsigned short max)
{
    unsigned short sum = prev + curr;
    prev = curr;
    sum = sum * 0x100 | sum >> 8;
    curr = sum;
    return sum % max;
}