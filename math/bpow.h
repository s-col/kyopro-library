#include <bits/stdc++.h>

// 累乗
template <typename _Ty>
_Ty bpow(_Ty a, int64_t n) {
    _Ty res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= a;
        a *= a;
    }
    return res;
}