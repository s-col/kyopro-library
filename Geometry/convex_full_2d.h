#include <bits/stdc++.h>

// This function returns the convex hull of the given points in counterclockwise order.
// complexity: O(N log N)
template <typename T>
std::vector<std::pair<T, T>> convex_hull_2d(std::vector<std::pair<T, T>> points) {
    auto is_cw = [](std::pair<T, T> a, std::pair<T, T> b, std::pair<T, T> c) -> bool {
        return (c.first - b.first) * a.second + (b.first - a.first) * c.second < (c.first - a.first) * b.second;
    };
    auto is_ccw = [](std::pair<T, T> a, std::pair<T, T> b, std::pair<T, T> c) -> bool {
        return (c.first - b.first) * a.second + (b.first - a.first) * c.second > (c.first - a.first) * b.second;
    };
    std::sort(points.begin(), points.end());
    std::vector<std::pair<T, T>> res;
    std::vector<std::pair<T, T>> stk;
    int n = static_cast<int>(points.size());
    for (int i = 0; i < n; i++) {
        while (true) {
            int sz = static_cast<int>(stk.size());
            if (sz < 2 || is_ccw(stk[sz - 2], stk[sz - 1], points[i])) break;
            stk.pop_back();
        }
        stk.push_back(points[i]);
    }
    res.insert(res.end(), stk.begin(), stk.end() - 1);
    stk.clear();
    for (int i = n - 1; i >= 0; i--) {
        while (true) {
            int sz = static_cast<int>(stk.size());
            if (sz < 2 || is_cw(points[i], stk[sz - 1], stk[sz - 2])) break;
            stk.pop_back();
        }
        stk.push_back(points[i]);
    }
    res.insert(res.end(), stk.begin(), stk.end() - 1);
    return res;
}