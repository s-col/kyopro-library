#include <bits/stdc++.h>

// ユークリッド互除法
template <typename T>
T gcd(T a, T b) {
    T r = a % b;
    while (r) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}