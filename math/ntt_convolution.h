#include <bits/stdc++.h>

#include "library/mod/ModInt.h"

// NTT による畳み込み (非再帰 ver.)
// 計算量：O(N log N) (N = |a| + |b|)
// require: ModInt
template <int_fast64_t Modulus, class T>
std::vector<ModInt<Modulus>> ntt_convolution(const std::vector<T>& a, const std::vector<T>& b) {
    using mint_t = ModInt<Modulus>;
    constexpr std::pair<mint_t, int> mod_info = []() -> std::pair<mint_t, int> {
        if (Modulus == 2) return {mint_t(1).pow(1), 0};
        if (Modulus == 167772161) return {mint_t(3).pow(5), 25};
        if (Modulus == 469762049) return {mint_t(3).pow(7), 26};
        if (Modulus == 754974721) return {mint_t(11).pow(45), 24};
        if (Modulus == 998244353) return {mint_t(3).pow(119), 23};
        // return {mint_t(p).pow(u), ord};
    }();  // {(primitive root).pow(u), log2(ord)} (Modulus = u * 2^ord + 1)
    const int na = static_cast<int>(a.size());
    const int nb = static_cast<int>(b.size());
    int sz = 1, deg = 0;
    while (sz < na + nb) {
        sz <<= 1, ++deg;
    }
    const mint_t gu = mod_info.first.pow(1ll << (mod_info.second - deg));
    std::vector<mint_t> ca(sz), cb(sz);
    for (int i = 0; i < na; i++) ca[i] = a[i];
    for (int i = 0; i < nb; i++) cb[i] = b[i];
    auto dft = [g = gu, d = deg](std::vector<mint_t>& vec, bool inverse = false) noexcept -> void {
        mint_t gbase = (inverse ? g.inv() : g);
        for (int i = 0; i < d; i++) {
            const int pdeg = 1 << (d - i - 1);
            for (int j = 0; j < (1 << i); j++) {
                mint_t gbase_k = 1;
                for (int k = 0; k < pdeg; k++) {
                    int cur = k + j * (pdeg << 1);
                    mint_t w1, w2;
                    w1 = vec[cur] + vec[cur + pdeg];
                    w2 = vec[cur] - vec[cur + pdeg];
                    vec[cur] = w1;
                    vec[cur + pdeg] = w2 * gbase_k;
                    gbase_k *= gbase;
                }
            }
            gbase *= gbase;
        }
        const int sz_vec = static_cast<int>(vec.size());
        std::vector<bool> is_done(sz_vec);
        for (int i = 0; i < sz_vec; i++) {
            if (!is_done[i]) {
                int j = 0, i_tmp = i, bits = d;
                while (bits--) {
                    j <<= 1, j |= (i_tmp & 1), i_tmp >>= 1;
                }
                std::swap(vec[i], vec[j]);
                is_done[i] = is_done[j] = true;
            }
        }
    };
    dft(ca), dft(cb);
    for (int i = 0; i < sz; i++) ca[i] *= cb[i];
    dft(ca, true);
    std::vector<mint_t> res(sz);
    for (int i = 0; i < sz; i++) res[i] = ca[i] / sz;
    return res;
}