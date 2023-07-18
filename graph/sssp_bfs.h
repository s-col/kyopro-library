#include <bits/stdc++.h>

#include "kyopro-library/graph/template.h"

// 単一始点最短経路問題(重み無し)
// BFS で重み無しグラフの単一始点最短経路問題を解く
// 時間計算量: O(E + V)
// 空間計算量: O(E + V)
// @param dist (O) dist[i] := s から i までの距離
// @param g (I) 重み無しグラフ
// @param s (I) 始点の頂点番号
template <typename T>
void sssp_bfs(std::vector<T>& dist, const Graph& g, int s) {
    constexpr T inf = std::numeric_limits<T>::max();
    dist.assign(g.size(), inf);
    std::queue<int> que;
    dist[s] = 0;
    que.emplace(s);
    while (!que.empty()) {
        const int u = que.front();
        que.pop();
        const int du = dist[u];
        for (const auto& to : g[u]) {
            if (dist[to] == inf) {
                dist[to] = du + 1;
                que.emplace(to);
            }
        }
    }
}
