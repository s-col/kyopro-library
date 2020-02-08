#include <bits/stdc++.h>

template <typename _Ty>
class UnionFind {
private:
    vector<_Ty> par;
    vector<_Ty> rank;

public:
    UnionFind(_Ty N) : par(N), rank(N) {
        for (_Ty i = 0; i < N; ++i) par[i] = i;
    }

    _Ty root(_Ty x) { return par[x] == x ? x : par[x] = root(par[x]); }

    bool same(_Ty x, _Ty y) { return root(x) == root(y); }

    void unite(_Ty x, _Ty y) {
        x = root(x);
        y = root(y);
        if (x == y) return;

        if (rank[x] < rank[y]) {
            par[x] = y;
        }
        else {
            par[y] = x;
            if (rank[x] == rank[y]) ++rank[x];
        }
    }
};