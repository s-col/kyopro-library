#include <bits/stdc++.h>

struct XorShift {
    uint32_t x = 123456789;
    uint32_t y = 362436069;
    uint32_t z = 521288629;
    uint32_t w = 88675123;
    double urand(void) noexcept {
        uint32_t t;
        t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w ^= t ^ (t >> 8) ^ (w >> 19);
        return w / 4294967296.0;
    }
    // node: [a, b]
    int randint(int a, int b) noexcept {
        return static_cast<int>(urand() * (b - a + 1)) + a;
    }
};