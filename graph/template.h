#include <bits/stdc++.h>

template <typename T>
struct WeightedEdge {
    int from, to;
    T cost;
    constexpr WeightedEdge(int to, T cost) noexcept : from(-1), to(to), cost(cost) {}
    constexpr WeightedEdge(int from, int to, T cost) noexcept : from(from), to(to), cost(cost) {}
};
template <typename T>
using WeightedGraph = std::vector<std::vector<WeightedEdge<T>>>;

using Graph = std::vector<std::vector<int>>;
