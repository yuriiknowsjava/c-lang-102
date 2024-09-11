#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <limits.h>

int setBit(const int data, const int position)
{
    return data | (1 << position);
}

int clearBit(const int data, const int position)
{
    return data & ~(1 << position);
}

int toggleBit(const int data, const int position)
{
    return data ^ (1 << position);
}

int checkBit(const int data, const int position)
{
    return (data & (1 << position)) != 0;
}

int countSetBits(const int data)
{
    int bitCount = 0;
    int mask = 1;
    for (size_t i = 0; i < sizeof(data) * 8; i++)
    {
        int test = data & mask;
        if (test != 0)
        {
            bitCount++;
        }
        mask <<= 1;
    }
    return bitCount;
}

int main()
{
    assert(setBit(5, 1) == 7);
    assert(setBit(5, 3) == 13);

    assert(clearBit(5, 0) == 4);
    assert(clearBit(5, 2) == 1);

    assert(toggleBit(5, 1) == 7);
    assert(toggleBit(5, 4) == 21);
    assert(toggleBit(5, 0) == 4);

    assert(checkBit(5, 2) == 1);
    assert(checkBit(5, 1) == 0);
    assert(checkBit(5, 0) == 1);

    assert(countSetBits(5) == 2);
    assert(countSetBits(7) == 3);
    assert(countSetBits(23) == 4);
    assert(countSetBits(1023) == 10);
}
