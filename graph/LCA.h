#include <bits/stdc++.h>

#include "template.h"

// LCA
// LCAを求める
// 時間計算量：
//     初期化：O(n log n)
//     LCAを一回求める：O(log n)
class LCA {
    using Adj = std::vector<std::vector<int>>;  // 隣接リスト

private:
    int n;                              // 要素数
    int logn;                           // floor(log2(n)) + 1
    int root;                           // 根
    std::vector<std::vector<int>> par;  // par[k][i]: i番目のノードの2^k番目の親
    std::vector<int> dep;               // 深さ

    void init(const Adj& g, int root) {
        n = static_cast<int>(g.size());
        root = root;

        logn = 1;
        while (n >> logn) ++logn;

        par.assign(logn, std::vector<int>(n, -1));
        dep.assign(n, -1);
        dfs(g, root, -1, 0);

        // parを初期化する
        for (int k = 0; k + 1 < logn; k++) {
            for (int i = 0; i < n; i++) {
                if (par[k][i] != -1)
                    par[k + 1][i] = par[k][par[k][i]];
            }
        }
    }
    // 初期化時にpar[0]やdepを求めるためのDFS
    void dfs(const Adj& g, int v, int p, int d) {
        par[0][v] = p;
        dep[v] = d;
        for (const auto& to : g[v]) {
            if (to != p) dfs(g, to, v, d + 1);
        }
    }

public:
    /**
     * コンストラクタ
     */
    LCA(const Adj& g, int root) {
        init(g, root);
    }
    // u と v のLCAを返す
    int lca(int u, int v) const {
        if (dep[u] > dep[v]) std::swap(u, v);

        // u と v の深さが同じになるまで親をたどる
        for (int k = 0; k < logn; k++) {
            if ((dep[v] - dep[u]) >> k & 1) {
                v = par[k][v];
            }
        }

        if (u == v) return u;

        // 二分探索する
        for (int k = logn - 1; k >= 0; k--) {
            if (par[k][u] != par[k][v]) {
                u = par[k][u];
                v = par[k][v];
            }
        }

        return par[0][u];
    }
    int parent(int idx, int d) const { return par[d][idx]; }
};