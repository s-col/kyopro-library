#include <bits/stdc++.h>

// セグメント木 SegmentTree<T>
// arguments:
//     _n: 要素数, _op: 二項演算, _identity: 単位元
// 時間計算量：
//     構築: O(N)
//     クエリ, 更新: O(log N)
template <class T>
class SegmentTree {
    using Op = std::function<T(T, T)>;

private:
    const Op op;
    const T ID;
    std::vector<T> vec;
    int sz;

public:
    explicit SegmentTree(int _n, Op _op, T _identity) noexcept
        : op(_op), ID(_identity) {
        sz = 1;
        while (sz < _n) sz <<= 1;
        vec.resize(sz * 2, ID);
    }
    explicit SegmentTree(const std::vector<T>& _vec, Op _op, T _identity) noexcept
        : op(_op), ID(_identity) {
        int n = _vec.size();
        sz = 1;
        while (sz < n) sz <<= 1;
        vec.resize(sz * 2, ID);
        set_array(_vec);
    }
    void set_value(int _idx, T _val) {
        vec[_idx + sz] = _val;
    }
    template <class RandomIt>
    void set_array(RandomIt _begin, RandomIt _end) {
        std::copy(_begin, _end, vec.begin() + sz);
    }
    void set_array(const std::vector<T>& _newvec) {
        set_array(_newvec.begin(), _newvec.end());
    }
    void build() noexcept {
        for (int i = sz - 1; i > 0; i--) {
            vec[i] = op(vec[i * 2], vec[i * 2 + 1]);
        }
    }
    void update(int _idx, T _val) {
        _idx += sz;
        vec[_idx] = _val;
        for (_idx >>= 1; _idx > 0; _idx >>= 1) {
            vec[_idx] = op(vec[_idx * 2], vec[_idx * 2 + 1]);
        }
    }
    T query(int _l, int _r) const {
        T l_val = ID, r_val = ID;
        _l += sz, _r += sz - 1;
        for (; _l <= _r; _l >>= 1, _r >>= 1) {
            if (_l & 1) l_val = op(l_val, vec[_l++]);
            if (!(_r & 1)) r_val = op(r_val, vec[_r--]);
        }
        return op(l_val, r_val);
    }
    const T& operator[](int _idx) {
        return vec[_idx + sz];
    }
};