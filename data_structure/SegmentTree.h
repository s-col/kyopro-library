#include <bits/stdc++.h>

// セグメント木 SegmentTree<T, Op>
//     T: 配列の要素の型, Op: 二項演算関数の型
// arguments:
//     n: 要素数, op: 二項演算, id: 単位元
// query は右半開区間
// 時間計算量：
//     構築: O(N)
//     クエリ, 更新: O(log N)
template <class T, class Op>
class SegmentTree {
private:
    const int n;
    const Op op;
    const T id;
    std::vector<T> vec;
    int sz;

public:
    explicit SegmentTree(int n, Op op, T id) noexcept
        : n(n), op(op), id(id) {
        sz = 1;
        while (sz < n) sz <<= 1;
        vec.assign(sz << 1, id);
    }
    explicit SegmentTree(const std::vector<T>& vec, Op op, T id) noexcept
        : n(vec.size()), op(op), id(id) {
        sz = 1;
        while (sz < n) sz <<= 1;
        this->vec.assign(sz << 1, id);
        set_array(vec);
    }
    T& operator[](int idx) noexcept {
        return vec[idx + sz];
    }
    void set_value(int idx, T val) noexcept {
        vec[idx + sz] = val;
    }
    template <class RandomIt>
    void set_array(RandomIt _begin, RandomIt _end) noexcept {
        std::copy(_begin, _end, vec.begin() + sz);
    }
    template <class Vec>
    void set_array(const Vec& v) noexcept {
        set_array(std::begin(v), std::end(v));
    }
    void build() noexcept {
        for (int i = sz - 1; i > 0; i--) {
            vec[i] = op(vec[i << 1], vec[(i << 1) | 1]);
        }
    }
    void update(int idx, T val) noexcept {
        idx += sz;
        vec[idx] = val;
        for (idx >>= 1; idx > 0; idx >>= 1) {
            vec[idx] = op(vec[idx << 1], vec[(idx << 1) | 1]);
        }
    }
    T query(int l, int r) const noexcept {
        T l_val = id, r_val = id;
        l += sz, r += sz - 1;
        for (; l <= r; l >>= 1, r >>= 1) {
            if (l & 1) l_val = op(l_val, vec[l++]);
            if (!(r & 1)) r_val = op(r_val, vec[r--]);
        }
        return op(l_val, r_val);
    }
    T query_all() const noexcept {
        return query(0, sz);
    }
    // Return the largest x such that check(A[idx] op ... op A[x - 1]) == true
    // complexity: O(log (n))
    template <class F>
    int max_right(int idx, const F& check) const noexcept {
        T acc = id;
        return idx < n ? _max_right(idx, check, acc, 1, 0, sz) : n;
    }
    // Return the smallest x such that check(A[x] op ... op A[idx - 1]) == true
    // complexity: O(log (n))
    template <class F>
    int min_left(int idx, const F& check) const noexcept {
        T acc = id;
        return idx > 0 ? _min_left(idx, check, acc, 1, 0, sz) : 0;
    }
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
        if (mid <= idx) return _max_right(idx, check, acc, (k << 1) | 1, mid, r);
        if (idx <= l) {
            T tmp = op(acc, vec[k]);
            if (check(tmp)) {
                acc = tmp;
                return n;
            }
        }
        const int vl = _max_right(idx, check, acc, k << 1, l, mid);
        if (vl < n) return vl;
        return _max_right(idx, check, acc, (k << 1) | 1, mid, r);
    }
    template <class F>
    int _min_left(int idx, const F& check, T& acc, int k, int l, int r) const noexcept {
        if (l + 1 == r) {
            acc = op(acc, vec[k]);
            return check(acc) ? 0 : k - sz + 1;
        }
        const int mid = (l + r) >> 1;
        if (mid >= idx) return _min_left(idx, check, acc, k << 1, l, mid);
        if (idx >= r) {
            T tmp = op(acc, vec[k]);
            if (check(tmp)) {
                acc = tmp;
                return 0;
            }
        }
        const int vr = _min_left(idx, check, acc, (k << 1) | 1, mid, r);
        if (vr > 0) return vr;
        return _min_left(idx, check, acc, k << 1, l, mid);
    }
};