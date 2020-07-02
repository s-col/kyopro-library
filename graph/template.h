#include <bits/stdc++.h>

// 重み付きグラフ(隣接リスト)
template <typename T>
struct Edge {
    int src, to;
    T cost;

    constexpr Edge(int to, T cost) noexcept
        : src(-1), to(to), cost(cost) {}
    constexpr Edge(int src, int to, T cost) noexcept
        : src(src), to(to), cost(cost) {}
};
template <typename T>
using WeightedGraph = std::vector<std::vector<Edge<T>>>;

// 重みなしグラフ(隣接リスト)
using Graph = std::vector<std::vector<int>>;