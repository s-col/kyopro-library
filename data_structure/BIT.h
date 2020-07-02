#include <bits/stdc++.h>

// BIT
// 0-indexed
// 時間計算量:
//     add, sum : O(log N)
template <typename T>
class BIT {
private:
    int n;
    std::vector<T> vec;

public:
    BIT(int n) : n(n), vec(n + 1) {}
    // i 番目の要素に a を足す
    void add(int i, const T& a) {
        for (++i; i <= n; i += i & (-i)) {
            vec[i] += a;
        }
    }
    // 区間[0, i)に対するクエリを実行する
    T query(int i) const {
        T res = 0;
        for (; i >= 1; i -= i & (-i)) {
            res += vec[i];
        }
        return res;
    }
    // 区間[i, j)に対するクエリを実行する
    T query(int i, int j) const {
        return query(j) - query(i);
    }
    size_t size() const noexcept {
        return n;
    }
    void reset() noexcept {
        std::fill(vec.begin(), vec.end(), static_cast<T>(0));
    }
};