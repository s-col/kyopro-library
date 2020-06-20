#include <bits/stdc++.h>

// 累乗
template <typename T>
T bpow(T a, int64_t n) {
    T res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= a;
        a *= a;
    }
    return res;
}