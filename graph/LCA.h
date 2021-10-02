#include <bits/stdc++.h>

// LCA
// LCAを求める
// 時間計算量：
//     初期化：O(n log n)
//     LCAを一回求める：O(log n)
class LCA {
    using Graph = std::vector<std::vector<int>>;

private:
    int n;
    int ub;
    int root;
    std::vector<std::vector<int>> par;
    std::vector<int> dep;

public:
    LCA(const Graph& g, int root) {
        init(g, root);
    }
    int lca(int u, int v) const {
        if (dep[u] > dep[v])
            std::swap(u, v);
        for (int k = 0; k < ub; k++) {
            if ((dep[v] - dep[u]) >> k & 1) {
                v = par[k][v];
            }
        }
        if (u == v)
            return u;
        for (int k = ub - 1; k >= 0; k--) {
            if (par[k][u] != par[k][v]) {
                u = par[k][u];
                v = par[k][v];
            }
        }
        return par[0][u];
    }
    int parent(int idx, int d) const {
        return par[d][idx];
    }
    int depth(int idx) const {
        return dep[idx];
    }
    int dist(int u, int v) const {
        return dep[u] + dep[v] - dep[lca(u, v)] * 2;
    }

private:
    void init(const Graph& g, int root) {
        n = static_cast<int>(g.size());
        root = root;
        ub = 1;
        while (n >> ub)
            ++ub;
        par.assign(ub, std::vector<int>(n, -1));
        dep.assign(n, -1);
        dfs(g, root, -1, 0);
        for (int k = 0; k + 1 < ub; k++) {
            for (int i = 0; i < n; i++) {
                if (par[k][i] != -1)
                    par[k + 1][i] = par[k][par[k][i]];
            }
        }
    }
    void dfs(const Graph& g, int v, int p, int d) {
        par[0][v] = p;
        dep[v] = d;
        for (const auto& to : g[v]) {
            if (to != p)
                dfs(g, to, v, d + 1);
        }
    }
};
