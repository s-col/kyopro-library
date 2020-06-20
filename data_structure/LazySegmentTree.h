#include <bits/stdc++.h>

// 遅延セグメント木(遅延)
//     T: 配列の要素の型
// arguments:
//     _n: 要素数
// 時間計算量：
//     構築: O(N)
//     クエリ, 更新: O(log N)
// NOTE: 抽象化未済
//       区間和・区間更新の実装になっている
template <typename T>
class LazySegmentTree {
private:
    std::vector<T> vec, lazy;
    int sz;

public:
    explicit LazySegmentTree(int _n) noexcept {
        sz = 1;
        while (sz < _n) sz <<= 1;
        vec.assign(sz * 2 - 1, 0);
        lazy.assign(sz * 2 - 1, 0);
    }
    void set_value(int idx, T val) noexcept {
        vec[sz - 1 + idx] = val;
    }
    void build() noexcept {
        for (int i = sz - 2; i >= 0; i--) {
            vec[i] = vec[i * 2 + 1] + vec[i * 2 + 2];
        }
    }
    void eval(int k, int l, int r) noexcept {
        if (lazy[k] == 0) return;
        vec[k] += lazy[k];
        if (r - l > 1) {
            lazy[k * 2 + 1] += lazy[k] / 2;
            lazy[k * 2 + 2] += lazy[k] / 2;
        }
        lazy[k] = 0;
    }
    void _update(int a, int b, T x, int k, int l, int r) noexcept {
        eval(k, l, r);
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            lazy[k] += x * (r - l);
            eval(k, l, r);
        }
        else {
            _update(a, b, x, k * 2 + 1, l, (l + r) >> 1);
            _update(a, b, x, k * 2 + 2, (l + r) >> 1, r);
            vec[k] = vec[k * 2 + 1] + vec[k * 2 + 2];
        }
    }
    void update(int a, int b, T x) noexcept {
        _update(a, b, x, 0, 0, sz);
    }
    T _query(int a, int b, int k, int l, int r) noexcept {
        if (b <= l || r <= a) return 0;
        eval(k, l, r);
        if (a <= l && r <= b)
            return vec[k];
        else {
            T res = _query(a, b, k * 2 + 1, l, (l + r) >> 1);
            res += _query(a, b, k * 2 + 2, (l + r) >> 1, r);
            return res;
        }
    }
    T query(int a, int b) noexcept {
        return _query(a, b, 0, 0, sz);
    }
};