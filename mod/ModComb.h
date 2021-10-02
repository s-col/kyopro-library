#include <bits/stdc++.h>

#include "kyopro-library/mod/ModInt.h"

// 二項係数(mod)
// 要ModInt
template <std::int_fast64_t Modulus>
class ModComb {
    using i64 = int_fast64_t;
    using Vm = std::vector<ModInt<Modulus>>;

private:
    Vm fac, inv, finv;

public:
    explicit ModComb(i64 n) noexcept : fac(n + 1), inv(n + 1), finv(n + 1) {
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (i64 i = 2; i < n + 1; ++i) {
            fac[i] = fac[i - 1] * i;
            inv[i] = Modulus - inv[Modulus % i] * (Modulus / i);
            finv[i] = finv[i - 1] * inv[i];
        }
    }

    ModInt<Modulus> comb(i64 n, i64 k) const noexcept {
        ModInt<Modulus> res;
        if (n < k || n < 0 || k < 0)
            res = 0;
        else
            res = fac[n] * finv[n - k] * finv[k];
        return res;
    }

    ModInt<Modulus> perm(i64 n, i64 k) const noexcept {
        ModInt<Modulus> res;
        if (n < k || n < 0 || k < 0)
            res = 0;
        else
            res = fac[n] * finv[n - k];
        return res;
    }

    ModInt<Modulus> get_fac(i64 n) const noexcept {
        return fac[n];
    }
    ModInt<Modulus> get_finv(i64 n) const noexcept {
        return finv[n];
    }
};
