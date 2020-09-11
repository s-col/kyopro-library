#include <bits/stdc++.h>

#include "template.h"

// 強連結成分分解
// arguments:
//     (O) res: res[i] = i 番目の頂点のトポロジカル順序
//     (I) g: グラフ
// return:
//     強連結成分の個数
// 計算量: O(|E| + |V|)
int scc(std::vector<int>& res, const Graph& g) {
    const int sz = static_cast<int>(g.size());
    Graph rg(sz);
    for (int i = 0; i < sz; i++) {
        for (const auto& v : g[i]) {
            rg[v].emplace_back(i);
        }
    }
    res.resize(sz);
    int cur = 0;
    std::vector<int> vs(sz);
    std::vector<bool> used(sz);
    auto dfs1 = [&](auto&& self, int idx) -> void {
        used[idx] = true;
        for (const auto& v : g[idx])
            if (!used[v]) self(self, v);
        vs[cur++] = idx;
    };
    auto dfs2 = [&](auto&& self, int idx, int k) -> void {
        used[idx] = true;
        res[idx] = k;
        for (const auto& v : rg[idx])
            if (!used[v]) self(self, v, k);
    };
    for (int i = 0; i < sz; i++) {
        if (!used[i]) dfs1(dfs1, i);
    }
    used.assign(sz, false);
    int ord = 0;
    for (int i = sz - 1; i >= 0; i--) {
        if (!used[vs[i]]) dfs2(dfs2, vs[i], ord++);
    }
    return ord;
}