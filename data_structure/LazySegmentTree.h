#include <bits/stdc++.h>

// 遅延評価セグメント木
// 参考：https://beet-aizu.hatenablog.com/entry/2017/12/01/225955
// template:
//     T : 配列のクラス
//     E : 作用素のクラス
// param:
//     n : 配列の長さ
//     f(T, T) -> T : 区間をマージする二項演算
//     g(T, E) -> T : 区間に作用する作用素
//     h(E, E) -> E : 作用素をマージする二項演算 (ただし，h(e1, e2)(t) = e2(e1(t)))
//     p(E, int) -> E : 作用素を比例的に拡大する変換
//     tid : T の単位元
//     eid : E の単位元
// method:
//     update : O(log N)
//     query : O(log N) (右半開区間)
template <class T, class E, class F, class G, class H, class P>
class LazySegmentTree {
private:
    const int n;
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
    explicit LazySegmentTree(int n, F f, G g, H h, P p, T tid, E eid) noexcept
        : n(n), f(f), g(g), h(h), p(p), tid(tid), eid(eid) {
        sz = 1;
        while (sz < n)
            sz <<= 1;
        vec.assign(sz * 2, tid);
        lazy.assign(sz * 2, eid);
    }
    explicit LazySegmentTree(const std::vector<T>& vec, F f, G g, H h, P p, T tid, E eid) noexcept
        : n(vec.size()), f(f), g(g), h(h), p(p), tid(tid), eid(eid) {
        sz = 1;
        while (sz < n)
            sz <<= 1;
        this->vec.assign(sz * 2, tid);
        lazy.assign(sz * 2, eid);
        set_array(vec);
    }
    T& operator[](int idx) noexcept {
        return vec[sz + idx];
    }
    void set_value(int idx, T val) noexcept {
        vec[sz + idx] = val;
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
            vec[i] = f(vec[i << 1], vec[(i << 1) | 1]);
        }
    }
    void update(int a, int b, E x) noexcept {
        _update(a, b, x, 1, 0, sz);
    }
    T query(int a, int b) noexcept {
        return _query(a, b, 1, 0, sz);
    }
    T query_all() noexcept {
        return query(0, sz);
    }
    // Return the largest x such that check(A[idx] op ... op A[x - 1]) == true
    // complexity: O(log (n))
    template <class C>
    int max_right(int idx, const C& check) noexcept {
        T acc = tid;
        return idx < n ? _max_right(idx, check, acc, 1, 0, sz) : n;
    }
    // Return the smallest x such that check(A[x] op ... op A[idx - 1]) == true
    // complexity: O(log (n))
    template <class C>
    int min_left(int idx, const C& check) noexcept {
        T acc = tid;
        return idx > 0 ? _min_left(idx, check, acc, 1, 0, sz) : 0;
    }

private:
    void eval(int k, int l, int r) noexcept {
        if (lazy[k] == eid)
            return;
        if (r - l > 1) {
            lazy[k << 1] = h(lazy[k << 1], lazy[k]);
            lazy[(k << 1) | 1] = h(lazy[(k << 1) | 1], lazy[k]);
        }
        vec[k] = g(vec[k], p(lazy[k], r - l));
        lazy[k] = eid;
    }
    T _update(int a, int b, E x, int k, int l, int r) noexcept {
        eval(k, l, r);
        if (b <= l || r <= a)
            return vec[k];
        if (a <= l && r <= b) {
            lazy[k] = h(lazy[k], x);
            return g(vec[k], p(lazy[k], r - l));
        } else {
            const T t1 = _update(a, b, x, k << 1, l, (l + r) >> 1);
            const T t2 = _update(a, b, x, (k << 1) | 1, (l + r) >> 1, r);
            return vec[k] = f(t1, t2);
        }
    }
    T _query(int a, int b, int k, int l, int r) noexcept {
        if (b <= l || r <= a)
            return tid;
        eval(k, l, r);
        if (a <= l && r <= b) {
            return vec[k];
        } else {
            const T t1 = _query(a, b, k << 1, l, (l + r) >> 1);
            const T t2 = _query(a, b, (k << 1) | 1, (l + r) >> 1, r);
            return f(t1, t2);
        }
    }
    template <class C>
    int _max_right(int idx, const C& check, T& acc, int k, int l, int r) noexcept {
        eval(k, l, r);
        if (l + 1 == r) {
            acc = f(acc, vec[k]);
            return check(acc) ? n : k - sz;
        }
        const int mid = (l + r) >> 1;
        if (mid <= idx)
            return _max_right(idx, check, acc, (k << 1) | 1, mid, r);
        if (idx <= l) {
            const T tmp = f(acc, vec[k]);
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
    template <class C>
    int _min_left(int idx, const C& check, T& acc, int k, int l, int r) noexcept {
        eval(k, l, r);
        if (l + 1 == r) {
            acc = f(acc, vec[k]);
            return check(acc) ? 0 : k - sz + 1;
        }
        const int mid = (l + r) >> 1;
        if (mid >= idx)
            return _min_left(idx, check, acc, k << 1, l, mid);
        if (idx >= r) {
            const T tmp = f(acc, vec[k]);
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