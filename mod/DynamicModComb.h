#include <bits/stdc++.h>

#include "kyopro-library/mod/DynamicModInt.h"

// 二項係数(mod)
// require: DynamicModInt
// NOTE: Modulus は素数でなければならない
template <const std::int_fast64_t& Modulus>
class DynamicModComb {
    using i64 = int_fast64_t;
    using Vm = std::vector<DynamicModInt<Modulus>>;

private:
    Vm fac, inv, finv;

public:
    explicit DynamicModComb(i64 n) noexcept : fac(n + 1), inv(n + 1), finv(n + 1) {
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (i64 i = 2; i < n + 1; ++i) {
            fac[i] = fac[i - 1] * i;
            inv[i] = Modulus - inv[Modulus % i] * (Modulus / i);
            finv[i] = finv[i - 1] * inv[i];
        }
    }

    DynamicModInt<Modulus> comb(i64 n, i64 k) const noexcept {
        DynamicModInt<Modulus> res;
        if (n < k || n < 0 || k < 0)
            res = 0;
        else
            res = fac[n] * finv[n - k] * finv[k];
        return res;
    }

    DynamicModInt<Modulus> perm(i64 n, i64 k) const noexcept {
        DynamicModInt<Modulus> res;
        if (n < k || n < 0 || k < 0)
            res = 0;
        else
            res = fac[n] * finv[n - k];
        return res;
    }

    DynamicModInt<Modulus> get_fac(i64 n) const noexcept { return fac[n]; }
    DynamicModInt<Modulus> get_finv(i64 n) const noexcept { return finv[n]; }
};
