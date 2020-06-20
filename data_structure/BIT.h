#include <bits/stdc++.h>

// BIT
// 0-indexed
// 時間計算量:
//     add, sum : O(log N)
template <typename T>
class BIT {
private:
    size_t m_n;
    std::vector<T> m_vec;

public:
    BIT(size_t num) : m_n(num), m_vec(num + 1) {}
    // i 番目の要素に a を足す
    void add(size_t i, const T& a) {
        for (++i; i <= m_n; i += i & (-i)) {
            m_vec[i] += a;
        }
    }
    // 区間[0, i)に対するクエリを実行する
    T query(size_t i) const {
        T res = 0;
        for (; i >= 1; i -= i & (-i)) {
            res += m_vec[i];
        }
        return res;
    }
    // 区間[i, j)に対するクエリを実行する
    T query(size_t i, size_t j) const {
        return query(j) - query(i);
    }
    size_t size() const noexcept {
        return m_n;
    }
    void assign(const T& a) {
        std::fill(m_vec.begin(), m_vec.end(), a);
    }
};