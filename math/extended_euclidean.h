#include <bits/stdc++.h>

// 拡張ユークリッド互除法
// 一次不定方程式 ax + by = gcd(a, b) を解く
template <typename T>
void extended_euclidean(T& x, T& y, const T& a, const T& b) {
    T x, y, u, v, s, t, k;
    s = a;
    t = b;
    x = 1;
    y = 0;
    u = 0;
    v = 1;
    while (t) {
        k = s / t;
        s -= k * t;
        swap(s, t);
        x -= k * u;
        swap(x, u);
        y -= k * v;
        swap(y, v);
    }
}