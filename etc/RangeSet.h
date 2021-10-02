#include <bits/stdc++.h>

template <class T>
class RangeSet {
private:
    std::set<std::pair<T, T>> data;
    static constexpr T INF = std::numeric_limits<T>::max();

public:
    RangeSet() noexcept {
        data.emplace(-INF, -INF);
        data.emplace(INF, INF);
    }
    const std::set<std::pair<T, T>>& get_data() const noexcept {
        return data;
    }
    std::set<std::pair<T, T>>& get_data() noexcept {
        return data;
    }
    // Insert [a, a + 1)
    void insert(T a) noexcept {
        insert(a, a + 1);
    }
    // Insert [a, b)
    void insert(T a, T b) noexcept {
        auto itr = std::prev(data.lower_bound({a, b}));
        if (itr->first <= a && a <= itr->second) {
            a = std::min(a, itr->first);
            b = std::max(b, itr->second);
            data.erase(itr);
        }
        itr = data.lower_bound({a, b});
        while (true) {
            if (a <= itr->first && itr->first <= b) {
                b = std::max(b, itr->second);
                itr = data.erase(itr);
            } else {
                break;
            }
        }
        data.emplace(a, b);
    }
    // Check whether the RangeSet contains the integer a.
    bool contains(T a) const noexcept {
        auto itr = std::prev(data.lower_bound({a + 1, a + 1}));
        return itr->first <= a && a < itr->second;
    }
    // Return the largest integer x such that x <= a and x is not contains in the RangeSet.
    T max_left(T a) const noexcept {
        auto itr = std::prev(data.lower_bound({a + 1, a + 1}));
        if (itr->first <= a && a < itr->second) {
            return itr->first - 1;
        } else {
            return a;
        }
    }
    // Return the smallest integer x such that x >= a and x is not contains in the RangeSet.
    T min_right(T a) const noexcept {
        auto itr = std::prev(data.lower_bound({a + 1, a + 1}));
        if (itr->first <= a && a < itr->second) {
            return itr->second;
        } else {
            return a;
        }
    }
};