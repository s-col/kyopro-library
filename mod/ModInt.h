#include <bits/stdc++.h>

// ModInt
//
// 宣言:
// ModInt<1000000007> mi;
// ModInt<1000000007> mi(917856986);
//
template <std::int_fast64_t Modulus>
class ModInt {
    using i64 = std::int_fast64_t;

    // friend
    template <std::int_fast64_t _MOD>
    friend std::istream& operator>>(std::istream& is, ModInt<_MOD>& rhs);
    template <std::int_fast64_t _MOD>
    friend std::ostream& operator<<(std::ostream& os, const ModInt<_MOD>& rhs);

private:
    i64 m_value;

public:
    /**
     * コンストラクタ
     */
    constexpr ModInt(const i64 x = 0) noexcept : m_value(x % Modulus) {
        if (m_value < 0) m_value += Modulus;
    }

    constexpr const i64& value() const noexcept { return m_value; }

    constexpr ModInt operator+(const ModInt& rhs) const noexcept {
        return ModInt(*this) += rhs;
    }
    constexpr ModInt operator-(const ModInt& rhs) const noexcept {
        return ModInt(*this) -= rhs;
    }
    constexpr ModInt operator*(const ModInt& rhs) const noexcept {
        return ModInt(*this) *= rhs;
    }
    constexpr ModInt operator/(const ModInt& rhs) const noexcept {
        return ModInt(*this) /= rhs;
    }

    constexpr ModInt& operator+=(const ModInt rhs) noexcept {
        m_value += rhs.m_value;
        if (m_value >= Modulus) {
            m_value -= Modulus;
        }
        return *this;
    }
    constexpr ModInt& operator-=(const ModInt rhs) noexcept {
        if (m_value < rhs.m_value) {
            m_value += Modulus;
        }
        m_value -= rhs.m_value;
        return *this;
    }
    constexpr ModInt& operator*=(const ModInt rhs) noexcept {
        m_value = m_value * rhs.m_value % Modulus;
        return *this;
    }
    constexpr ModInt& operator/=(ModInt rhs) noexcept {
        i64 exp = Modulus - 2;
        while (exp) {
            if (exp & 1) {
                *this *= rhs;
            }
            rhs *= rhs;
            exp >>= 1;
        }
        return *this;
    }

    constexpr ModInt& operator++() noexcept {
        *this += 1;
        return *this;
    }
    constexpr ModInt operator++(int) noexcept {
        ModInt res = *this;
        *this += 1;
        return res;
    }
    constexpr ModInt& operator--() noexcept {
        *this -= 1;
        return *this;
    }
    constexpr ModInt operator--(int) noexcept {
        ModInt res = *this;
        *this -= 1;
        return res;
    }

    constexpr bool operator<(const ModInt& rhs) const noexcept {
        return m_value < rhs.m_value;
    }
    constexpr bool operator>(const ModInt& rhs) const noexcept {
        return m_value > rhs.m_value;
    }
    constexpr bool operator<=(const ModInt& rhs) const noexcept {
        return m_value <= rhs.m_value;
    }
    constexpr bool operator>=(const ModInt& rhs) const noexcept {
        return m_value >= rhs.m_value;
    }
    constexpr bool operator==(const ModInt& rhs) const noexcept {
        return m_value == rhs.m_value;
    }

    constexpr ModInt pow(i64 k) const noexcept {
        ModInt res = 1;
        ModInt tmp = *this;
        for (; k > 0; k >>= 1) {
            if (k & 1) res *= tmp;
            tmp *= tmp;
        }
        return res;
    }

    constexpr ModInt inverse() const noexcept {
        i64 q = m_value;
        i64 b = Modulus, u = 1, v = 0;
        while (b) {
            i64 t = q / b;
            q -= t * b;
            swap(q, b);
            u -= t * v;
            swap(u, v);
        }
        u %= Modulus;
        if (u < 0) u += Modulus;
        return u;
    }
};

// iostream用の関数[ModInt]
template <std::int_fast64_t Modulus>
std::istream& operator>>(std::istream& is, ModInt<Modulus>& rhs) {
    is >> rhs.m_value;
    return is;
}
template <std::int_fast64_t Modulus>
std::ostream& operator<<(std::ostream& os, const ModInt<Modulus>& rhs) {
    os << rhs.m_value;
    return os;
}
