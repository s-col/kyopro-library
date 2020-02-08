#include <bits/stdc++.h>

// ユークリッド互除法
template <typename _Ty>
_Ty gcd(_Ty a, _Ty b) {
    _Ty r = a % b;
    while (r) {
        a = b;
        b = r;
        r = a % b;
    }
    return b;
}