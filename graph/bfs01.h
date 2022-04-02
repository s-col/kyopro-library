#include <bits/stdc++.h>

#include "kyopro-library/graph/template.h"


// 01BFS
// 頂点sから各頂点への最短距離を求める (辺の重みは 0 or 1 でなければならない)
// 時間計算量 : O(E + V)
// arguments:
//     (O) dist: dist[i] = s から i までの距離
//     (I) g: 重み付きグラフ
//     (I) s: 始点
template <class T>
void bfs01(std::vector<T>& dist, const WeightedGraph<T>& g, int s) {
    constexpr T inf = std::numeric_limits<T>::max();
    dist.assign(g.size(), inf);

    using Pi = std::pair<T, int>;
    std::deque<Pi> q;
    dist[s] = 0;
    q.emplace_back(dist[s], s);
    while (!q.empty()) {
        auto [cost, idx] = q.front();
        q.pop_front();
        if (cost > dist[idx])
            continue;
        for (const auto& edge : g[idx]) {
            T next_cost = cost + edge.cost;
            if (next_cost >= dist[edge.to])
                continue;
            dist[edge.to] = next_cost;
            if (edge.cost == 0)
                q.emplace_front(next_cost, edge.to);
            else
                q.emplace_back(next_cost, edge.to);
        }
    }
}
