#include <bits/stdc++.h>

/**
 * @brief Run-length encoding.
 *
 * Compresses consecutive equal values into (value, count) pairs.
 *
 * @tparam V Container type supporting operator[] and size().
 * @param a Input sequence.
 * @return Vector of {value, length} pairs.
 * @complexity O(N)
 */
template <class V>
std::vector<std::pair<typename V::value_type, int>> rle(const V& a) {
    std::vector<std::pair<typename V::value_type, int>> res;
    int sz = a.size();
    int i = 0;
    while (i < sz) {
        int j = i;
        while (j < sz && a[j] == a[i])
            ++j;
        res.emplace_back(a[i], j - i);
        i = j;
    }
    return res;
}
