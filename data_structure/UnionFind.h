#include <bits/stdc++.h>

/**
 * @brief Disjoint Set Union structure.
 *
 * Supports union and find operations with union by size and path
 * compression. All operations are effectively \f$O(\alpha(N))\f$.
 */
class UnionFind {
private:
    std::vector<int> par;
    std::vector<int> sz;

public:
    /**
     * @brief Construct an UnionFind with N elements.
     * @param N Number of elements.
     */
    UnionFind(int N) : par(N), sz(N, 1) {
        for (int i = 0; i < N; ++i)
            par[i] = i;
    }
    /**
     * @brief Find the representative of x.
     * @param x Element index.
     * @return Root index of x.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    int root(int x) {
        return par[x] == x ? x : par[x] = root(par[x]);
    }
    /**
     * @brief Test whether x and y belong to the same set.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    bool same(int x, int y) {
        return root(x) == root(y);
    }
    /**
     * @brief Unite the sets containing x and y.
     *
     * @param x First element index.
     * @param y Second element index.
     * @return The representative of the merged set.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
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
    /**
     * @brief Return the size of the set containing x.
     * @param x Element index.
     * @return Number of elements in x's set.
     */
    int size(int x) {
        return sz[root(x)];
    }
    /**
     * @brief Reset the structure with a new universe of size N.
     * @param N Number of elements.
     */
    void reset(int N) {
        par.resize(N);
        for (int i = 0; i < N; ++i)
            par[i] = i;
        sz.assign(N, 1);
    }
};
