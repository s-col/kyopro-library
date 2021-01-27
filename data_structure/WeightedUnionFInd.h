#include <bits/stdc++.h>

template <typename T>
class WeightedUnionFind {
private:
    std::vector<int> par;
    std::vector<int> sz;
    std::vector<T> potential;
    const T id;

public:
    WeightedUnionFind(int N, T id) : par(N), sz(N, 1), potential(N, id), id(id) {
        for (int i = 0; i < N; ++i) par[i] = i;
    }
    int root(int x) {
        if (par[x] == x) {
            return x;
        } else {
            int rt = root(par[x]);
            potential[x] += potential[par[x]];
            return par[x] = rt;
        }
    }
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    T weight(int x) {
        root(x);
        return potential[x];
    }
    // Return weight(y) - weight(x)
    T diff(int x, int y) {
        return weight(y) - weight(x);
    }
    // The weight is set to satisfy weight(y) = weight(x) + w;
    void unite(int x, int y, T w) {
        w += weight(x), w -= weight(y);
        x = root(x), y = root(y);
        if (x == y) return;
        if (sz[x] < sz[y]) std::swap(x, y), w = -w;
        par[y] = x;
        sz[x] += sz[y];
        potential[y] = w;
    }
    int size(int x) {
        return sz[root(x)];
    }
    void reset(int N) {
        par.resize(N);
        for (int i = 0; i < N; ++i) par[i] = i;
        sz.assign(N, 1);
        potential.assign(N, id);
    }
};