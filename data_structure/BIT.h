#include <bits/stdc++.h>

/**
 * @brief Binary Indexed Tree (Fenwick Tree).
 *
 * Supports prefix sum queries and point updates in \f$O(\log N)\f$ time.
 * All indices are 0-based externally.
 *
 * @tparam T Element type.
 */
template <typename T>
class BIT {
private:
    int n;
    std::vector<T> vec;

public:
    /**
     * @brief Construct a new BIT of size n.
     *
     * @param n Number of elements.
     */
    BIT(int n) : n(n), vec(n + 1) {}

    /**
     * @brief Add value a to index i.
     *
     * @param i 0-based index to update.
     * @param a Value to add.
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    void add(int i, const T& a) {
        for (++i; i <= n; i += i & (-i)) {
            vec[i] += a;
        }
    }

    /**
     * @brief Prefix sum on [0, i).
     *
     * @param i Exclusive end index.
     * @return Sum of elements in [0, i).
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    T query(int i) const {
        T res = 0;
        for (; i >= 1; i -= i & (-i)) {
            res += vec[i];
        }
        return res;
    }

    /**
     * @brief Range sum query on [i, j).
     *
     * @param i Left inclusive index.
     * @param j Right exclusive index.
     * @return Sum of elements in [i, j).
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    T query(int i, int j) const {
        return query(j) - query(i);
    }

    /**
     * @brief Return the number of elements handled by the tree.
     */
    size_t size() const noexcept {
        return n;
    }

    /**
     * @brief Clear all elements to zero.
     */
    void reset() noexcept {
        std::fill(vec.begin(), vec.end(), static_cast<T>(0));
    }
};