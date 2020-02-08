#include <bits/stdc++.h>

// BIT
// 0-indexed
// 時間計算量:
//     add, sum : O(log N)
template <typename _Ty>
class BIT {
private:
    size_t m_n;
    std::vector<_Ty> m_vec;

public:
    BIT(size_t num) : m_n(num), m_vec(num + 1) {}

    // i 番目の要素に a を足す
    void add(size_t i, const _Ty& a) {
        for (++i; i <= m_n; i += i & (-i)) {
            m_vec[i] += a;
        }
    }

    // 区間[0, i)の総和を求める
    _Ty sum(size_t i) const {
        _Ty res = 0;
        for (++i; i >= 1; i -= i & (-i)) {
            res += m_vec[i];
        }
        return res;
    }

    // 区間[i, j)の総和を求める
    _Ty sum(size_t i, size_t j) const {
        return sum(j) - sum(i);
    }

    size_t size() const noexcept {
        return m_n;
    }

    void assign(const _Ty& a) {
        std::fill(m_vec.begin(), m_vec.end(), a);
    }
};