#include <bits/stdc++.h>

/**
 * @brief Weighted Union-Find structure.
 *
 * Disjoint-set data structure that also stores potential differences
 * between nodes. Typical operations such as union and find work in
 * amortized \f$\alpha(N)\f$ time.
 *
 * @tparam T Type of the potential (weight).
 */
template <typename T>
class WeightedUnionFind {
private:
    std::vector<int> par;
    std::vector<int> sz;
    std::vector<T> potential;
    const T id;

public:
    /**
     * @brief Construct a new WeightedUnionFind instance.
     *
     * @param N Number of elements.
     * @param id Identity element for potential values.
     */
    WeightedUnionFind(int N, T id) : par(N), sz(N, 1), potential(N, id), id(id) {
        for (int i = 0; i < N; ++i)
            par[i] = i;
    }

    /**
     * @brief Find the representative of x.
     *
     * Path compression is used to keep the complexity nearly constant.
     *
     * @param x Index of the element.
     * @return Root index of the set containing x.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    int root(int x) {
        if (par[x] == x) {
            return x;
        } else {
            const int rt = root(par[x]);
            potential[x] += potential[par[x]];
            return par[x] = rt;
        }
    }
    /**
     * @brief Check whether two nodes are in the same set.
     *
     * @param x First node index.
     * @param y Second node index.
     * @return true if x and y belong to the same set.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    bool same(int x, int y) {
        return root(x) == root(y);
    }

    /**
     * @brief Get the potential of node x.
     *
     * @param x Node index.
     * @return Potential value of x relative to its root.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    T weight(int x) {
        root(x);
        return potential[x];
    }

    /**
     * @brief Compute weight(y) - weight(x).
     *
     * @param x Base node.
     * @param y Target node.
     * @return Difference weight(y) - weight(x).
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    T diff(int x, int y) {
        return weight(y) - weight(x);
    }

    /**
     * @brief Unite two nodes with a given potential difference.
     *
     * After union, the invariant weight(y) = weight(x) + w holds.
     *
     * @param x First node index.
     * @param y Second node index.
     * @param w Value to satisfy weight(y) = weight(x) + w.
     *
     * Time complexity: amortized \f$O(\alpha(N))\f$.
     */
    void unite(int x, int y, T w) {
        w += weight(x), w -= weight(y);
        x = root(x), y = root(y);
        if (x == y)
            return;
        if (sz[x] < sz[y])
            std::swap(x, y), w = -w;
        par[y] = x;
        sz[x] += sz[y];
        potential[y] = w;
    }
    /**
     * @brief Size of the set containing x.
     *
     * @param x Node index.
     * @return Number of nodes in the set of x.
     */
    int size(int x) {
        return sz[root(x)];
    }

    /**
     * @brief Reset the structure with N elements.
     *
     * @param N Number of new elements.
     */
    void reset(int N) {
        par.resize(N);
        for (int i = 0; i < N; ++i)
            par[i] = i;
        sz.assign(N, 1);
        potential.assign(N, id);
    }
};