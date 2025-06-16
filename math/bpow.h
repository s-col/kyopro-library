#include <bits/stdc++.h>

/**
 * @brief Binary exponentiation $a^n$.
 *
 * Computes the power via repeated squaring.
 *
 * @tparam T Multiplicative type supporting operator*.
 * @param a Base value.
 * @param n Non-negative exponent.
 * @return a raised to the n-th power.
 * @complexity O(log n)
 */
template <typename T>
T bpow(T a, int64_t n) {
    T res = 1;
    for (; n > 0; n >>= 1) {
        if (n & 1) res *= a;
        a *= a;
    }
    return res;
}
