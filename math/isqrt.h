#include <bits/stdc++.h>

template <typename T>
T isqrt(T x) {
    T x0 = x / 2;
    if (x0 == 0) {
        return x;
    }
    T x1 = (x0 + x / x0) / 2;
    while (x1 < x0) {
        x0 = x1;
        x1 = (x0 + x / x0) / 2;
    }
    return x0;
}
