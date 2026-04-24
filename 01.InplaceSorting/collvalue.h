#pragma once

#include <utility>

struct CollInt
{
    int value;

    static int comps;
    static int swaps;
    static int moves;

    CollInt(int v = 0) : value(v) {}

    CollInt(const CollInt& other)
    {
        value = other.value;
        ++moves;
    }

    CollInt& operator=(const CollInt& other)
    {
        value = other.value;
        ++moves;
        return *this;
    }

    bool operator<(const CollInt& other) const
    {
        ++comps;
        return value < other.value;
    }

    static void reset()
    {
        comps = 0;
        swaps = 0;
        moves = 0;
    }

    friend void swap(CollInt& a, CollInt& b)
    {
        using std::swap;
        swap(a.value, b.value);
        ++swaps;
    }
};

int CollInt::comps = 0;
int CollInt::swaps = 0;
int CollInt::moves = 0;