#include <bits/stdc++.h>

template <typename _Ty>
class UnionFind {
private:
    vector<_Ty> par;
    vector<_Ty> sz;

public:
    UnionFind(_Ty N) : par(N), sz(N, 1) {
        for (_Ty i = 0; i < N; ++i) par[i] = i;
    }

    _Ty root(_Ty x) {
        return par[x] == x ? x : par[x] = root(par[x]);
    }

    bool same(_Ty x, _Ty y) {
        return root(x) == root(y);
    }

    void unite(_Ty x, _Ty y) {
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }

    _Ty size(_Ty x) {
        return sz[root(x)];
    }
};