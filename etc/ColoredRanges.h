#include <bits/stdc++.h>

template <class Value = std::int64_t>
class ColoredRanges {
    using Color = std::int64_t;

    static constexpr Value VALUE_MIN = std::numeric_limits<Value>::min();
    static constexpr Value VALUE_MAX = std::numeric_limits<Value>::max();

    std::map<Value, Color> left2color;
    const Color null_color;

public:
    ColoredRanges(Color null_color = -1) noexcept : left2color(), null_color(null_color) {
        left2color[VALUE_MIN] = null_color;
        left2color[VALUE_MAX] = null_color;
    }

    void paint(Value l, Value r, Color c) noexcept {
        left2color[l] = std::prev(left2color.upper_bound(l))->second;
        left2color[r] = std::prev(left2color.upper_bound(r))->second;
        for (auto itr = left2color.find(l); itr->first != r; itr = left2color.erase(itr))
            ;
        left2color[l] = c;
    }

    void erase(Value l, Value r) noexcept {
        paint(l, r, null_color);
    }

    std::vector<std::pair<Value, Value>> get_ranges_by_color(Color c) const noexcept {
        std::vector<std::pair<Value, Value>> res;
        for (auto itr = left2color.begin(); itr != left2color.end(); ++itr) {
            if (itr->second == null_color) {
                continue;
            }
            if (itr->second == c) {
                if (!res.empty() && res.back().second == itr->first) {
                    res.back().second = std::next(itr)->first;
                } else {
                    res.emplace_back(itr->first, std::next(itr)->first);
                }
            }
        }
        return res;
    }

    std::unordered_map<Color, std::vector<std::pair<Value, Value>>> get_all_ranges() const noexcept {
        std::unordered_map<Color, std::vector<std::pair<Value, Value>>> res;
        for (auto itr = left2color.begin(); itr != left2color.end(); ++itr) {
            if (itr->second == null_color) {
                continue;
            }
            auto& ranges = res[itr->second];
            if (!ranges.empty() && ranges.back().second == itr->first) {
                ranges.back().second = std::next(itr)->first;
            } else {
                ranges.emplace_back(itr->first, std::next(itr)->first);
            }
        }
        return res;
    }

    Color get_color(Value x) const noexcept {
        return std::prev(left2color.upper_bound(x))->second;
    }

    Color get_null_color() const noexcept {
        return null_color;
    }
};
