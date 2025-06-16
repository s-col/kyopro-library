#include <bits/stdc++.h>

#include "kyopro-library/graph/template.h"

/**
 * @brief Dijkstra's shortest path algorithm.
 *
 * Computes single-source shortest paths on a graph with non-negative
 * edge weights.
 *
 * @tparam T Weight type.
 * @param dist Output array storing distances from s.
 * @param g Weighted graph adjacency list.
 * @param s Source vertex index.
 *
 * Time complexity: \f$O((E+V) \log V)\f$.
 */
template <typename T>
void dijkstra(std::vector<T>& dist, const WeightedGraph<T>& g, int s) {
    constexpr T inf = std::numeric_limits<T>::max();
    dist.assign(g.size(), inf);

    using Pi = std::pair<T, int>;
    std::priority_queue<Pi, std::vector<Pi>, std::greater<Pi>> q;
    dist[s] = 0;
    q.emplace(dist[s], s);
    while (!q.empty()) {
        auto [cost, idx] = q.top();
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

/**
 * @brief Dijkstra's algorithm that also records the previous vertex.
 *
 * Allows reconstruction of the shortest path tree.
 *
 * @tparam T Weight type.
 * @param dist Output distances from s.
 * @param prev Output parent array: prev[v] is the predecessor of v.
 * @param g Weighted graph adjacency list.
 * @param s Source vertex index.
 *
 * Time complexity: \f$O((E+V) \log V)\f$.
 */
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
        auto [cost, idx] = q.top();
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
