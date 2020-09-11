#include <bits/stdc++.h>

template <typename T>
struct WeightedEdge {
    int to;
    T cost;
    constexpr Edge(int to, T cost = -1) noexcept : to(to), cost(cost) {}
};
template <typename T>
using WeightedGraph = std::vector<std::vector<WeightedEdge>>;

using Graph = std::vector<std::vector<int>>;