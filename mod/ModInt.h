#include <bits/stdc++.h>

// ModInt
template <std::int_fast64_t Modulus>
class ModInt {
    using i64 = std::int_fast64_t;

private:
    i64 m_value;

public:
    constexpr ModInt(const i64 x = 0) noexcept : m_value(x) {
        if (m_value < -Modulus || m_value >= Modulus) m_value %= Modulus;
        if (m_value < 0) m_value += Modulus;
    }

    constexpr i64 const& value() const noexcept { return m_value; }

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
        m_value *= rhs.m_value;
        if (m_value >= Modulus) m_value %= Modulus;
        return *this;
    }
    constexpr ModInt& operator/=(ModInt rhs) noexcept {
        *this *= rhs.inv();
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

    constexpr ModInt inv() const noexcept {
        i64 q = m_value;
        i64 b = Modulus, u = 1, v = 0;
        i64 tmp = 0;
        while (b) {
            i64 t = q / b;
            q -= t * b;
            tmp = q, q = b, b = tmp;
            u -= t * v;
            tmp = u, u = v, v = tmp;
        }
        if (u < -Modulus || u >= Modulus) u %= Modulus;
        if (u < 0) u += Modulus;
        return u;
    }

    constexpr ModInt pow(i64 k) const noexcept {
        ModInt res = 1;
        ModInt tmp = 0;
        if (k < 0) {
            tmp = this->inv();
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

    friend constexpr ModInt operator+(const ModInt& a) noexcept {
        return a;
    }
    friend constexpr ModInt operator-(const ModInt& a) noexcept {
        return ModInt(0) - a;
    }
    friend constexpr ModInt operator+(const ModInt& lhs, const ModInt& rhs) noexcept {
        return ModInt<Modulus>(lhs) += rhs;
    }
    friend constexpr ModInt operator-(const ModInt& lhs, const ModInt& rhs) noexcept {
        return ModInt<Modulus>(lhs) -= rhs;
    }
    friend constexpr ModInt operator*(const ModInt& lhs, const ModInt& rhs) noexcept {
        return ModInt<Modulus>(lhs) *= rhs;
    }
    friend constexpr ModInt operator/(const ModInt& lhs, const ModInt& rhs) noexcept {
        return ModInt<Modulus>(lhs) /= rhs;
    }

    friend constexpr bool operator<(const ModInt& lhs, const ModInt& rhs) noexcept {
        return lhs.m_value < rhs.m_value;
    }
    friend constexpr bool operator>(const ModInt& lhs, const ModInt& rhs) noexcept {
        return lhs.m_value > rhs.m_value;
    }
    friend constexpr bool operator<=(const ModInt& lhs, const ModInt& rhs) noexcept {
        return lhs.m_value <= rhs.m_value;
    }
    friend constexpr bool operator>=(const ModInt& lhs, const ModInt& rhs) noexcept {
        return lhs.m_value >= rhs.m_value;
    }

    friend constexpr bool operator==(const ModInt& lhs, const ModInt& rhs) noexcept {
        return lhs.m_value == rhs.m_value;
    }
    friend constexpr bool operator!=(const ModInt& lhs, const ModInt& rhs) noexcept {
        return lhs.m_value != rhs.m_value;
    }

    friend std::istream& operator>>(std::istream& is, ModInt& rhs) {
        i64 a;
        is >> a;
        rhs = a;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const ModInt& rhs) {
        os << rhs.m_value;
        return os;
    }
};

constexpr long long MOD = 1000000007;
using Mint = ModInt<MOD>;
