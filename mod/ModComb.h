#include <bits/stdc++.h>

#include "ModInt.h"

// 二項係数(mod)
// 要ModInt
template <std::int_fast64_t Modulus>
class ModComb {
    using i64 = int_fast64_t;
    using Vl = std::vector<i64>;

private:
    Vl fac, inv, finv;

public:
    explicit ModComb(i64 n) noexcept : fac(n + 1), inv(n + 1), finv(n + 1) {
        fac[0] = fac[1] = 1;
        finv[0] = finv[1] = 1;
        inv[1] = 1;
        for (i64 i = 2; i < n + 1; ++i) {
            fac[i] = fac[i - 1] * i % Modulus;
            inv[i] = Modulus - inv[Modulus % i] * (Modulus / i) % Modulus;
            finv[i] = finv[i - 1] * inv[i] % Modulus;
        }
    }

    ModInt<Modulus> comb(i64 n, i64 k) const noexcept {
        ModInt<Modulus> res;
        if (n < k)
            res = 0;
        else if (n < 0 || k < 0)
            res = 0;
        else
            res = fac[n] * (finv[n - k] * finv[k] % Modulus) % Modulus;
        return res;
    }

    ModInt<Modulus> get_fac(i64 n) const noexcept { return ModInt<Modulus>(fac[n]); }
    ModInt<Modulus> get_finv(i64 n) const noexcept { return ModInt<Modulus>(finv[n]); }
};