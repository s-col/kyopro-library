#include <bits/stdc++.h>

class UnionFind {
private:
    std::vector<int> par;
    std::vector<int> sz;

public:
    UnionFind(int N) : par(N), sz(N, 1) {
        for (int i = 0; i < N; ++i)
            par[i] = i;
    }
    int root(int x) {
        return par[x] == x ? x : par[x] = root(par[x]);
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    // @return x, y をマージ後の集合の代表元
    int unite(int x, int y) {
        x = root(x);
        y = root(y);
        if (x == y)
            return x;
        if (sz[x] < sz[y])
            std::swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return x;
    }
    int size(int x) {
        return sz[root(x)];
    }
    void reset(int N) {
        par.resize(N);
        for (int i = 0; i < N; ++i)
            par[i] = i;
        sz.assign(N, 1);
    }
};
