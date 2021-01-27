#include <bits/stdc++.h>

// DynamicModInt
// NOTE: Modulus の参照先は静的領域に無ければならない
template <const std::int_fast64_t& Modulus>
class DynamicModInt {
    using i64 = std::int_fast64_t;

private:
    i64 m_value;

public:
    constexpr DynamicModInt(const i64 x = 0) noexcept : m_value(x % Modulus) {
        if (m_value < 0) m_value += Modulus;
    }

    constexpr i64 const& value() const noexcept { return m_value; }

    constexpr DynamicModInt& operator+=(const DynamicModInt rhs) noexcept {
        m_value += rhs.m_value;
        if (m_value >= Modulus) {
            m_value -= Modulus;
        }
        return *this;
    }
    constexpr DynamicModInt& operator-=(const DynamicModInt rhs) noexcept {
        if (m_value < rhs.m_value) {
            m_value += Modulus;
        }
        m_value -= rhs.m_value;
        return *this;
    }
    constexpr DynamicModInt& operator*=(const DynamicModInt rhs) noexcept {
        m_value = m_value * rhs.m_value % Modulus;
        return *this;
    }
    constexpr DynamicModInt& operator/=(DynamicModInt rhs) noexcept {
        *this *= rhs.inv();
        return *this;
    }

    constexpr DynamicModInt& operator++() noexcept {
        *this += 1;
        return *this;
    }
    constexpr DynamicModInt operator++(int) noexcept {
        DynamicModInt res = *this;
        *this += 1;
        return res;
    }
    constexpr DynamicModInt& operator--() noexcept {
        *this -= 1;
        return *this;
    }
    constexpr DynamicModInt operator--(int) noexcept {
        DynamicModInt res = *this;
        *this -= 1;
        return res;
    }

    constexpr DynamicModInt inv() const noexcept {
        i64 q = m_value;
        i64 b = Modulus, u = 1, v = 0;
        while (b) {
            i64 t = q / b;
            q -= t * b;
            std::swap(q, b);
            u -= t * v;
            std::swap(u, v);
        }
        u %= Modulus;
        if (u < 0) u += Modulus;
        return u;
    }

    constexpr DynamicModInt pow(i64 k) const noexcept {
        DynamicModInt res = 1;
        DynamicModInt tmp;
        if (k < 0) {
            tmp = (*this).inv();
            k = -k;
        } else {
            tmp = *this;
        }
        for (; k > 0; k >>= 1) {
            if (k & 1) res *= tmp;
            tmp *= tmp;
        }
        return res;
    }

    friend constexpr DynamicModInt operator+(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return DynamicModInt<Modulus>(lhs) += rhs;
    }
    friend constexpr DynamicModInt operator-(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return DynamicModInt<Modulus>(lhs) -= rhs;
    }
    friend constexpr DynamicModInt operator*(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return DynamicModInt<Modulus>(lhs) *= rhs;
    }
    friend constexpr DynamicModInt operator/(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return DynamicModInt<Modulus>(lhs) /= rhs;
    }

    friend constexpr bool operator<(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return lhs.m_value < rhs.m_value;
    }
    friend constexpr bool operator>(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return lhs.m_value > rhs.m_value;
    }
    friend constexpr bool operator<=(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return lhs.m_value <= rhs.m_value;
    }
    friend constexpr bool operator>=(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return lhs.m_value >= rhs.m_value;
    }

    friend constexpr bool operator==(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return lhs.m_value == rhs.m_value;
    }
    friend constexpr bool operator!=(const DynamicModInt& lhs, const DynamicModInt& rhs) noexcept {
        return lhs.m_value != rhs.m_value;
    }

    friend std::istream& operator>>(std::istream& is, DynamicModInt& rhs) {
        i64 a;
        is >> a;
        rhs = a;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const DynamicModInt& rhs) {
        os << rhs.m_value;
        return os;
    }
};

std::int_fast64_t MOD;
using Mint = DynamicModInt<MOD>;
