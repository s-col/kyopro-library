#include <bits/stdc++.h>

template <typename T>
struct WeightedEdge {
    int from, to;
    T cost;
    constexpr WeightedEdge(int to, T cost) noexcept : from(-1), to(to), cost(cost) {}
    constexpr WeightedEdge(int from, int to, T cost) noexcept : from(from), to(to), cost(cost) {}
};
struct WeightedEdgeLess {
    template <typename T>
    constexpr bool operator()(const WeightedEdge<T>& e1, const WeightedEdge<T>& e2) const noexcept {
        return e1.cost < e2.cost;
    }
};
struct WeightEdgeGreater {
    template <typename T>
    constexpr bool operator()(const WeightedEdge<T>& e1, const WeightedEdge<T>& e2) const noexcept {
        return e1.cost > e2.cost;
    }
};
template <typename T>
using WeightedGraph = std::vector<std::vector<WeightedEdge<T>>>;
