#include <bits/stdc++.h>

#include "kyopro-library/graph/template.h"

// グラフが二部グラフかを判定
// 時間計算量: O(E)
// return:
//     g が二部グラフなら片方のグループの頂点数
//     g が二部グラフでないなら -1
// verified: https://atcoder.jp/contests/abc327/submissions/47279144
int is_bipartite(const Graph& g) {
    const int n = static_cast<int>(g.size());
    std::vector<int> colors(n);
    int white_cnt = 0;

    auto dfs = [&](auto&& self, int u, int color) -> bool {
        colors[u] = color;
        if (color == 1) {
            ++white_cnt;
        }
        for (const auto& to : g[u]) {
            if (colors[to] == color) {
                return false;
            }
            if (colors[to] == 0) {
                if (!self(self, to, -color)) {
                    return false;
                }
            }
        }
        return true;
    };

    for (int u = 0; u < n; u++) {
        if (colors[u] != 0)
            continue;
        if (!dfs(dfs, u, 1)) {
            return -1;
        }
    }

    return white_cnt;
}
