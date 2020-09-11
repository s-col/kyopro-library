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
    const Op op;
    const T id;
    std::vector<T> vec;
    int sz;

public:
    explicit SegmentTree(int n, Op op, T id) noexcept
        : op(op), id(id) {
        sz = 1;
        while (sz < n) sz <<= 1;
        vec.assign(sz * 2, id);
    }
    explicit SegmentTree(const std::vector<T>& vec, Op op, T id) noexcept
        : op(op), id(id) {
        int n = vec.size();
        sz = 1;
        while (sz < n) sz <<= 1;
        this->vec.assign(sz * 2, id);
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
    void set_array(const std::vector<T>& vec) noexcept {
        set_array(vec.begin(), vec.end());
    }
    void build() noexcept {
        for (int i = sz - 1; i > 0; i--) {
            vec[i] = op(vec[i * 2], vec[i * 2 + 1]);
        }
    }
    void update(int idx, T val) noexcept {
        idx += sz;
        vec[idx] = val;
        for (idx >>= 1; idx > 0; idx >>= 1) {
            vec[idx] = op(vec[idx * 2], vec[idx * 2 + 1]);
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
    void reset() noexcept {
        std::fill(vec.begin(), vec.end(), id);
    }
};