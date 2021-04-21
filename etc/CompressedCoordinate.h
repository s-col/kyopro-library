#include <bits/stdc++.h>

template <typename T>
class CompressedCoordinate {
private:
    std::vector<T> pos;

public:
    CompressedCoordinate() noexcept {}
    explicit CompressedCoordinate(const std::vector<T>& vec) noexcept : pos(vec) {}
    void add(const T& p_new) noexcept {
        pos.emplace_back(p_new);
    }
    void build() noexcept {
        std::sort(pos.begin(), pos.end());
        pos.erase(std::unique(pos.begin(), pos.end()), pos.end());
    }
    size_t lower_bound(const T& key) const noexcept {
        return std::lower_bound(pos.begin(), pos.end(), key) - pos.begin();
    }
    size_t upper_bound(const T& key) const noexcept {
        return std::upper_bound(pos.begin(), pos.end(), key) - pos.begin();
    }
    size_t operator[](const T& key) const noexcept {
        return lower_bound(key);
    }
    size_t size() const noexcept {
        return pos.size();
    }
};