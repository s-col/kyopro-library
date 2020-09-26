#include <bits/stdc++.h>

// 遅延評価セグメント木
// 参考：https://beet-aizu.hatenablog.com/entry/2017/12/01/225955
// template:
//     T : 配列のクラス
//     E : 作用素のクラス
// param:
//     n : 配列の長さ
//     f : 区間をマージする二項演算
//     g : 区間に作用する作用素
//     h : 作用素をマージする二項演算
//     p : 作用素を比例的に拡大する変換
//     tid : T の単位元
//     eid : E の単位元
// method:
//     update : O(log N)
//     query : O(log N) (右半開区間)
template <class T, class E, class F, class G, class H, class P>
class LazySegmentTree {
private:
    const F f;
    const G g;
    const H h;
    const P p;
    const T tid;
    const E eid;
    std::vector<T> vec;
    std::vector<E> lazy;
    int sz;

public:
    explicit LazySegmentTree(
        int n, F f, G g, H h, P p, T tid, E eid) noexcept
        : f(f), g(g), h(h), p(p), tid(tid), eid(eid) {
        sz = 1;
        while (sz < n) sz <<= 1;
        vec.assign(sz * 2 - 1, tid);
        lazy.assign(sz * 2 - 1, eid);
    }
    T& operator[](int idx) noexcept {
        return vec[sz - 1 + idx];
    }
    void set_value(int idx, T val) noexcept {
        vec[sz - 1 + idx] = val;
    }
    void build() noexcept {
        for (int i = sz - 2; i >= 0; i--) {
            vec[i] = f(vec[i * 2 + 1], vec[i * 2 + 2]);
        }
    }
    void update(int a, int b, E x) noexcept {
        _update(a, b, x, 0, 0, sz);
    }
    T query(int a, int b) noexcept {
        return _query(a, b, 0, 0, sz);
    }

private:
    void eval(int k, int l, int r) noexcept {
        if (lazy[k] == eid) return;
        if (r - l > 1) {
            lazy[k * 2 + 1] = h(lazy[k * 2 + 1], lazy[k]);
            lazy[k * 2 + 2] = h(lazy[k * 2 + 2], lazy[k]);
        }
        vec[k] = g(vec[k], p(lazy[k], r - l));
        lazy[k] = eid;
    }
    T _update(int a, int b, E x, int k, int l, int r) noexcept {
        eval(k, l, r);
        if (b <= l || r <= a) return vec[k];
        if (a <= l && r <= b) {
            lazy[k] = h(lazy[k], x);
            return g(vec[k], p(lazy[k], r - l));
        }
        else {
            T t1 = _update(a, b, x, k * 2 + 1, l, (l + r) >> 1);
            T t2 = _update(a, b, x, k * 2 + 2, (l + r) >> 1, r);
            return vec[k] = f(t1, t2);
        }
    }
    T _query(int a, int b, int k, int l, int r) noexcept {
        if (b <= l || r <= a) return tid;
        eval(k, l, r);
        if (a <= l && r <= b) {
            return vec[k];
        }
        else {
            T t1 = _query(a, b, k * 2 + 1, l, (l + r) >> 1);
            T t2 = _query(a, b, k * 2 + 2, (l + r) >> 1, r);
            return f(t1, t2);
        }
    }
};
