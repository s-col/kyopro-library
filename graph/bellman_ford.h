#include <bits/stdc++.h>

#include "kyopro-library/graph/template.h"

// ベルマンフォード法
// 頂点sから各頂点までの最短距離を求める
// 負の距離が存在してもok
// 時間計算量：O(VE)
// arguments:
//     (O) dist: dist[i] = s から i までの距離
//     (I) g: 重み付きグラフ
//     (I) s: 始点
// return:
//     負閉路が無ければ true
template <typename T>
bool bellman_ford(std::vector<T>& dist, const WeightedGraph<T>& g, int s) {
    T inf = std::numeric_limits<T>::max();
    int n = static_cast<int>(g.size());
    dist.assign(n, inf);
    dist[s] = 0;
    bool update;
    for (int i = 0; i < n; i++) {
        update = false;
        for (int j = 0; j < n; j++) {
            for (const auto& edge : g[j]) {
                if (dist[j] != inf && dist[edge.to] > dist[j] + edge.cost) {
                    dist[edge.to] = dist[j] + edge.cost;
                    update = true;
                }
            }
        }
        if (!update) break;
    }
    if (update) {
        dist.clear();
        return false;
    }
    else {
        return true;
    }
}

// ベルマンフォード法(prev付き)
// 頂点sから各頂点までの最短距離を求める
// 負の距離が存在してもok
// 閉路の検出にも使える
// 時間計算量：O(VE)
// arguments:
//     (O) dist: dist[i] = s から i までの距離
//     (O) prev: prev[i] = i のひとつ前の頂点番号
//     (I) g: 重み付きグラフ
//     (I) s: 始点
// return:
//     負閉路が無ければ true
template <typename T>
bool bellman_ford(std::vector<T>& dist, std::vector<int>& prev, const WeightedGraph<T>& g, int s) {
    T inf = std::numeric_limits<T>::max();
    int n = static_cast<int>(g.size());
    prev.assign(n, -1);
    dist.assign(n, inf);
    dist[s] = 0;
    prev[s] = -1;
    bool update;
    for (int i = 0; i < n; i++) {
        update = false;
        for (int j = 0; j < n; j++) {
            for (const auto& edge : g[j]) {
                if (dist[j] != inf && dist[edge.to] > dist[j] + edge.cost) {
                    dist[edge.to] = dist[j] + edge.cost;
                    prev[edge.to] = j;
                    update = true;
                }
            }
        }
        if (!update) break;
    }
    if (update) {
        dist.clear();
        prev.clear();
        return false;
    }
    else {
        return true;
    }
}