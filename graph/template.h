#include <bits/stdc++.h>

// 重み付きグラフ(隣接リスト)
template <typename _Ty>
struct Edge {
    int src, to;
    _Ty cost;

    constexpr Edge(int _to, _Ty _cost) noexcept
        : src(-1), to(_to), cost(_cost) {}
    constexpr Edge(int _src, int _to, _Ty _cost) noexcept
        : src(_src), to(_to), cost(_cost) {}
};
template <typename _Ty>
using WeightedGraph = std::vector<std::vector<Edge<_Ty>>>;

// 重みなしグラフ(隣接リスト)
using Graph = std::vector<std::vector<int>>;