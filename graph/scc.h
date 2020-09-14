#include <bits/stdc++.h>

#include "template.h"

// 強連結成分分解
// arguments:
//     (I) g: グラフ
// return:
//     res: res[i] = (i 番目の強連結成分を構成する頂点番号を格納した vector)
// 計算量: O(|E| + |V|)
std::vector<std::vector<int>> scc(const Graph& g) {
    const int sz = static_cast<int>(g.size());
    Graph rg(sz);
    for (int i = 0; i < sz; i++) {
        for (const auto& v : g[i]) {
            rg[v].emplace_back(i);
        }
    }
    int cur = 0;
    std::vector<std::vector<int>> res;
    std::vector<int> vs(sz);
    std::vector<bool> used(sz);
    auto dfs1 = [&](auto&& self, int idx) -> void {
        used[idx] = true;
        for (const auto& v : g[idx])
            if (!used[v]) self(self, v);
        vs[cur++] = idx;
    };
    auto dfs2 = [&](auto&& self, int idx) -> void {
        used[idx] = true;
        res.back().emplace_back(idx);
        for (const auto& v : rg[idx])
            if (!used[v]) self(self, v);
    };
    for (int i = 0; i < sz; i++) {
        if (!used[i]) dfs1(dfs1, i);
    }
    used.assign(sz, false);
    for (int i = sz - 1; i >= 0; i--) {
        if (!used[vs[i]]) {
            res.emplace_back();
            dfs2(dfs2, vs[i]);
        }
    }
    return res;
}