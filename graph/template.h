#include <bits/stdc++.h>

// 重み付きグラフ(隣接リスト)
template <typename T>
struct Edge {
    int src, to;
    T cost;

    constexpr Edge(int _to, T _cost) noexcept
        : src(-1), to(_to), cost(_cost) {}
    constexpr Edge(int _src, int _to, T _cost) noexcept
        : src(_src), to(_to), cost(_cost) {}
};
template <typename T>
using WeightedGraph = std::vector<std::vector<Edge<T>>>;

// 重みなしグラフ(隣接リスト)
using Graph = std::vector<std::vector<int>>;