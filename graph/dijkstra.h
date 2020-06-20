#include <bits/stdc++.h>

#include "template.h"

// ダイクストラ法
// 頂点sから各頂点への最短距離を求める
// 時間計算量 : O((E + V)log(V))
// argument:
//     dist: dist[i] = 頂点sから頂点iまでの最短距離(出力)
//     g : 重み付きグラフ(隣接リスト)
//     s : スタートする頂点番号
template <typename T>
void dijkstra(std::vector<T>& dist, const WeightedGraph<T>& g, int s) {
    constexpr T inf = std::numeric_limits<T>::max();
    dist.assign(g.size(), inf);

    using Pi = std::pair<T, int>;
    std::priority_queue<Pi, std::vector<Pi>, std::greater<Pi>> q;
    dist[s] = 0;
    q.emplace(dist[s], s);
    while (!q.empty()) {
        T cost;
        int idx;
        tie(cost, idx) = q.top();
        q.pop();
        if (dist[idx] < cost) continue;
        for (const auto& edge : g[idx]) {
            T next_cost = cost + edge.cost;
            if (next_cost >= dist[edge.to]) continue;
            dist[edge.to] = next_cost;
            q.emplace(next_cost, edge.to);
        }
    }
}

// ダイクストラ法(prev付き)
// 頂点sから各頂点への最短距離を求める
// prevも返すので経路を求めることができる
// 時間計算量 : O((E + V)log(V))
// argument:
//     dist : 頂点sから頂点iまでの最短距離を格納する配列(出力)
//     prev : 一つ前の頂点番号を格納する配列(出力)
//     g : 重み付きグラフ(隣接リスト)
//     s : スタートする頂点番号
template <typename T>
void dijkstra(std::vector<T>& dist, std::vector<int>& prev,
              const WeightedGraph<T>& g, int s) {
    constexpr T inf = std::numeric_limits<T>::max();
    dist.assign(g.size(), inf);
    prev.assign(g.size(), -1);

    using Pi = std::pair<T, int>;
    std::priority_queue<Pi, std::vector<Pi>, std::greater<Pi>> q;
    dist[s] = 0;
    q.emplace(dist[s], s);
    while (!q.empty()) {
        T cost;
        int idx;
        tie(cost, idx) = q.top();
        q.pop();
        if (dist[idx] < cost) continue;
        for (const auto& edge : g[idx]) {
            T next_cost = cost + edge.cost;
            if (next_cost >= dist[edge.to]) continue;
            dist[edge.to] = next_cost;
            prev[edge.to] = idx;
            q.emplace(next_cost, edge.to);
        }
    }
}