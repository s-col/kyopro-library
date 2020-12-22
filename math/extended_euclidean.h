#include <bits/stdc++.h>

// 拡張ユークリッド互除法
// 一次不定方程式 ax + by = gcd(a, b) を解く
template <typename T>
constexpr std::pair<T, T> extended_euclidean(const T& a, const T& b) {
    T x = 1, y = 0, u = 0, v = 1, s = a, t = b;
    T k = 0, tmp = 0;
    while (t) {
        k = s / t, s -= k * t;
        tmp = s, s = t, t = tmp;
        x -= k * u;
        tmp = x, x = u, u = tmp;
        y -= k * v;
        tmp = y, y = v, v = tmp;
    }
    return {x, y};
}