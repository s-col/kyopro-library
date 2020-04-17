#include <bits/stdc++.h>

class UnionFind {
    using i64 = std::int64_t;

private:
    std::vector<i64> par;
    std::vector<i64> sz;

public:
    UnionFind(i64 N) : par(N), sz(N, 1) {
        for (i64 i = 0; i < N; ++i) par[i] = i;
    }
    i64 root(i64 x) {
        return par[x] == x ? x : par[x] = root(par[x]);
    }
    bool same(i64 x, i64 y) {
        return root(x) == root(y);
    }
    void unite(i64 x, i64 y) {
        x = root(x);
        y = root(y);
        if (x == y) return;
        if (sz[x] < sz[y]) std::swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
    }
    i64 size(i64 x) {
        return sz[root(x)];
    }
    void reset(i64 N) {
        par.resize(N);
        for (i64 i = 0; i < N; ++i) par[i] = i;
        sz.assign(N, 1);
    }
};