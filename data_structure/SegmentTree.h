#include <bits/stdc++.h>

/**
 * @brief Segment tree supporting range queries and point updates.
 *
 * Both build and query/update operations run in \f$O(\log N)\f$ time.
 * The query operates on right half-open intervals.
 *
 * @tparam T  Type of each element.
 * @tparam Op Binary operation type.
 */
template <class T, class Op>
class SegmentTree {
private:
    const int n;
    const Op op;
    const T id;
    std::vector<T> vec;
    int sz;

public:
    /**
     * @brief Construct a segment tree with given size.
     *
     * @param n  Number of elements.
     * @param op Binary operation.
     * @param id Identity element of op.
     */
    explicit SegmentTree(int n, Op op, T id) noexcept : n(n), op(op), id(id) {
        sz = 1;
        while (sz < n)
            sz <<= 1;
        vec.assign(sz << 1, id);
    }
    /**
     * @brief Construct from an initial array.
     *
     * @param vec Initial values.
     * @param op  Binary operation.
     * @param id  Identity element of op.
     */
    explicit SegmentTree(const std::vector<T>& vec, Op op, T id) noexcept
        : n(vec.size()), op(op), id(id) {
        sz = 1;
        while (sz < n)
            sz <<= 1;
        this->vec.assign(sz << 1, id);
        set_array(vec);
    }
    /**
     * @brief Access underlying element without updating.
     *
     * @param idx Index to access.
     * @return Reference to the element.
     */
    T& operator[](int idx) noexcept {
        return vec[idx + sz];
    }

    /**
     * @brief Set the value at a leaf without updating ancestors.
     */
    void set_value(int idx, T val) noexcept {
        vec[idx + sz] = val;
    }

    /**
     * @brief Set the leaves from a range.
     */
    template <class RandomIt>
    void set_array(RandomIt _begin, RandomIt _end) noexcept {
        std::copy(_begin, _end, vec.begin() + sz);
    }

    /**
     * @brief Set the leaves from a container.
     */
    template <class Vec>
    void set_array(const Vec& v) noexcept {
        set_array(std::begin(v), std::end(v));
    }

    /**
     * @brief Build the tree from current leaves.
     *
     * Time complexity: \f$O(N)\f$.
     */
    void build() noexcept {
        for (int i = sz - 1; i > 0; i--) {
            vec[i] = op(vec[i << 1], vec[(i << 1) | 1]);
        }
    }
    /**
     * @brief Point update of index idx.
     *
     * @param idx Index to update.
     * @param val New value.
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    void update(int idx, T val) noexcept {
        idx += sz;
        vec[idx] = val;
        for (idx >>= 1; idx > 0; idx >>= 1) {
            vec[idx] = op(vec[idx << 1], vec[(idx << 1) | 1]);
        }
    }
    /**
     * @brief Range query on [l, r).
     *
     * @param l Left index (inclusive).
     * @param r Right index (exclusive).
     * @return Aggregated value on the range.
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    T query(int l, int r) const noexcept {
        T l_val = id, r_val = id;
        l += sz, r += sz - 1;
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                l_val = op(l_val, vec[l++]);
            if (!(r & 1))
                r_val = op(vec[r--], r_val);
        }
        return op(l_val, r_val);
    }
    /**
     * @brief Query the whole range.
     */
    T query_all() const noexcept {
        return query(0, sz);
    }
    /**
     * @brief Return largest x such that check(A[idx] op ... op A[x-1]) is true.
     *
     * @tparam F Predicate type.
     * @param idx Starting index.
     * @param check Monotone predicate on prefix aggregate.
     * @return Largest position x (<= n).
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    template <class F>
    int max_right(int idx, const F& check) const noexcept {
        T acc = id;
        return idx < n ? _max_right(idx, check, acc, 1, 0, sz) : n;
    }

    /**
     * @brief Return smallest x such that check(A[x] op ... op A[idx-1]) is true.
     *
     * @tparam F Predicate type.
     * @param idx Ending index.
     * @param check Monotone predicate on suffix aggregate.
     * @return Smallest position x (>= 0).
     *
     * Time complexity: \f$O(\log N)\f$.
     */
    template <class F>
    int min_left(int idx, const F& check) const noexcept {
        T acc = id;
        return idx > 0 ? _min_left(idx, check, acc, 1, 0, sz) : 0;
    }

    /**
     * @brief Reset all values to the identity element.
     */
    void reset() noexcept {
        std::fill(vec.begin(), vec.end(), id);
    }

private:
    template <class F>
    int _max_right(int idx, const F& check, T& acc, int k, int l, int r) const noexcept {
        if (l + 1 == r) {
            acc = op(acc, vec[k]);
            return check(acc) ? n : k - sz;
        }
        const int mid = (l + r) >> 1;
        if (mid <= idx)
            return _max_right(idx, check, acc, (k << 1) | 1, mid, r);
        if (idx <= l) {
            T tmp = op(acc, vec[k]);
            if (check(tmp)) {
                acc = tmp;
                return n;
            }
        }
        const int vl = _max_right(idx, check, acc, k << 1, l, mid);
        if (vl < n)
            return vl;
        return _max_right(idx, check, acc, (k << 1) | 1, mid, r);
    }
    template <class F>
    int _min_left(int idx, const F& check, T& acc, int k, int l, int r) const noexcept {
        if (l + 1 == r) {
            acc = op(acc, vec[k]);
            return check(acc) ? 0 : k - sz + 1;
        }
        const int mid = (l + r) >> 1;
        if (mid >= idx)
            return _min_left(idx, check, acc, k << 1, l, mid);
        if (idx >= r) {
            T tmp = op(acc, vec[k]);
            if (check(tmp)) {
                acc = tmp;
                return 0;
            }
        }
        const int vr = _min_left(idx, check, acc, (k << 1) | 1, mid, r);
        if (vr > 0)
            return vr;
        return _min_left(idx, check, acc, k << 1, l, mid);
    }
};