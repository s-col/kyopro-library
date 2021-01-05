#include <bits/stdc++.h>

#include "kyopro-library/graph/template.h"

// グラフが二部グラフかを判定
// 時間計算量: O(E)
// return:
//     g が二部グラフなら片方のグループの頂点数
//     g が二部グラフでないなら -1
int is_bipartite(const Graph& g) {
    const int n = static_cast<int>(g.size());
    std::vector<int> colors(n);
    int white_cnt = 0;
    std::stack<std::pair<int, int>> st;
    st.emplace(0, 1);
    while (!st.empty()) {
        auto [v, color] = st.top();
        st.pop();
        if (color == 1) ++white_cnt;
        colors[v] = color;
        for (const auto& to : g[v]) {
            if (colors[to] == color) {
                return -1;
            }
            if (colors[to] == 0) {
                st.emplace(to, -color);
            }
        }
    }
    return white_cnt;
}