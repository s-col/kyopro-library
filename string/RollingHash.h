#include <bits/stdc++.h>

template <uint_fast64_t MOD>
class RollingHash {
    using u64 = uint_fast64_t;

private:
    const int sz;
    std::vector<u64> cum, pows;

public:
    explicit RollingHash(const std::string& s, u64 base) noexcept
        : sz(s.size()), cum(s.size() + 1), pows(s.size() + 1) {
        pows[0] = 1;
        for (int i = 0; i < sz; i++) {
            cum[i + 1] = (cum[i] * base + s[i]) % MOD;
            pows[i + 1] = pows[i] * base % MOD;
        }
    }
    u64 hash() const noexcept { return cum[sz]; }
    u64 hash(int l, int r) const noexcept {
        u64 res = cum[r] + MOD - cum[l] * pows[r - l] % MOD;
        if (res >= MOD) res -= MOD;
        return res;
    }
};