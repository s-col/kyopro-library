#include <bits/stdc++.h>


// FFT による畳み込み (非再帰 ver.)
// 計算量：O(N log N) (N = |a| + |b|)
template <typename T>
std::vector<double> fft_convolution(const std::vector<T>& a, const std::vector<T>& b) {
    struct Complex {
        double real, imag;
        constexpr Complex() noexcept : real(0), imag(0) {}
        constexpr Complex(double real) noexcept : real(real), imag(0) {}
        constexpr Complex(double real, double imag) noexcept : real(real), imag(imag) {}
        constexpr Complex& operator+=(const Complex r) noexcept {
            real += r.real, imag += r.imag;
            return *this;
        }
        constexpr Complex& operator-=(const Complex r) noexcept {
            real -= r.real, imag -= r.imag;
            return *this;
        }
        constexpr Complex& operator*=(const Complex r) noexcept {
            const double old_real = real, old_imag = imag;
            real = old_real * r.real - old_imag * r.imag;
            imag = r.real * old_imag + old_real * r.imag;
            return *this;
        }
        constexpr Complex& operator/=(const Complex r) noexcept {
            const double old_real = real, old_imag = imag;
            const double d = r.real * r.real + r.imag * r.imag;
            real = old_real * r.real + old_imag * r.imag;
            imag = r.real * old_imag - old_real * r.imag;
            real /= d, imag /= d;
            return *this;
        }
        constexpr Complex operator+() const noexcept {
            return *this;
        }
        constexpr Complex operator-() const noexcept {
            return Complex(0) - *this;
        }
        constexpr Complex operator+(const Complex& r) const noexcept {
            return Complex(*this) += r;
        }
        constexpr Complex operator-(const Complex& r) const noexcept {
            return Complex(*this) -= r;
        }
        constexpr Complex operator*(const Complex& r) const noexcept {
            return Complex(*this) *= r;
        }
        constexpr Complex operator/(const Complex& r) const noexcept {
            return Complex(*this) /= r;
        }
        static constexpr Complex polar(double x) noexcept {
            Complex res;
            res.real = std::cos(x), res.imag = std::sin(x);
            return res;
        }
    };
    const int na = static_cast<int>(a.size());
    const int nb = static_cast<int>(b.size());
    int sz = 1, deg = 0;
    while (sz < na + nb) {
        sz <<= 1, ++deg;
    }
    std::vector<Complex> ca(sz), cb(sz);
    for (int i = 0; i < na; i++) ca[i] = a[i];
    for (int i = 0; i < nb; i++) cb[i] = b[i];
    auto dft = [](std::vector<Complex>& vec, int d, bool inverse = false) noexcept -> void {
        constexpr double PI = std::acos(-1);
        const double sgn = inverse ? -1.0 : 1.0;
        for (int i = 0; i < d; i++) {
            const int pdeg = 1 << (d - i - 1);
            const double omega = -2.0 * sgn * PI / (pdeg << 1);
            for (int j = 0; j < (1 << i); j++) {
                for (int k = 0; k < pdeg; k++) {
                    int cur = k + j * (pdeg << 1);
                    Complex w1, w2;
                    w1 = vec[cur] + vec[cur + pdeg];
                    w2 = vec[cur] - vec[cur + pdeg];
                    vec[cur] = w1;
                    vec[cur + pdeg] = w2 * Complex::polar(omega * k);
                }
            }
        }
        const int sz_vec = static_cast<int>(vec.size());
        std::vector<bool> is_done(sz_vec);
        for (int i = 0; i < sz_vec; i++) {
            if (!is_done[i]) {
                int j = 0, i_tmp = i, bits = d;
                while (bits--) {
                    j <<= 1, j |= (i_tmp & 1), i_tmp >>= 1;
                }
                std::swap(vec[i], vec[j]);
                is_done[i] = is_done[j] = true;
            }
        }
    };
    dft(ca, deg), dft(cb, deg);
    for (int i = 0; i < sz; i++) ca[i] *= cb[i];
    dft(ca, deg, true);
    std::vector<double> res(sz);
    for (int i = 0; i < sz; i++) res[i] = ca[i].real / sz;
    return res;
}


// FFT による畳み込み (再帰 ver.)
// 計算量：O(N log N) (N = |a| + |b|)
template <typename T>
std::vector<double> fft_convolution(const std::vector<T>& a, const std::vector<T>& b) {
    struct Comprex {
        double real, imag;
        constexpr Comprex() noexcept : real(0), imag(0) {}
        constexpr Comprex(double real) noexcept : real(real), imag(0) {}
        constexpr Comprex(double real, double imag) noexcept : real(real), imag(imag) {}
        constexpr Comprex& operator+=(const Comprex r) noexcept {
            real += r.real, imag += r.imag;
            return *this;
        }
        constexpr Comprex& operator-=(const Comprex r) noexcept {
            real -= r.real, imag -= r.imag;
            return *this;
        }
        constexpr Comprex& operator*=(const Comprex r) noexcept {
            const double old_real = real, old_imag = imag;
            real = old_real * r.real - old_imag * r.imag;
            imag = r.real * old_imag + old_real * r.imag;
            return *this;
        }
        constexpr Comprex& operator/=(const Comprex r) noexcept {
            const double old_real = real, old_imag = imag;
            const double d = r.real * r.real + r.imag * r.imag;
            real = old_real * r.real + old_imag * r.imag;
            imag = r.real * old_imag - old_real * r.imag;
            real /= d, imag /= d;
            return *this;
        }
        constexpr Comprex operator+() const noexcept {
            return *this;
        }
        constexpr Comprex operator-() const noexcept {
            return Comprex(0) - *this;
        }
        constexpr Comprex operator+(const Comprex& r) const noexcept {
            return Comprex(*this) += r;
        }
        constexpr Comprex operator-(const Comprex& r) const noexcept {
            return Comprex(*this) -= r;
        }
        constexpr Comprex operator*(const Comprex& r) const noexcept {
            return Comprex(*this) *= r;
        }
        constexpr Comprex operator/(const Comprex& r) const noexcept {
            return Comprex(*this) /= r;
        }
        static constexpr Comprex polar(double x) noexcept {
            Comprex res;
            res.real = std::cos(x), res.imag = std::sin(x);
            return res;
        }
    };
    const int na = static_cast<int>(a.size());
    const int nb = static_cast<int>(b.size());
    int sz = 1;
    while (sz < na + nb) sz <<= 1;
    std::vector<Comprex> ca(sz), cb(sz);
    for (int i = 0; i < na; i++) ca[i] = a[i];
    for (int i = 0; i < nb; i++) cb[i] = b[i];
    auto dft = [](auto&& self, std::vector<Comprex>& vec, bool inverse = false) noexcept -> void {
        const int sz_vec = static_cast<int>(vec.size());
        if (sz_vec == 1) return;
        std::vector<Comprex> vec_a, vec_b;
        vec_a.reserve(sz_vec >> 1), vec_b.reserve(sz_vec >> 1);
        for (int i = 0; i < (sz_vec >> 1); i++) {
            vec_a.emplace_back(vec[i << 1]);
            vec_b.emplace_back(vec[(i << 1) + 1]);
        }
        self(self, vec_a, inverse), self(self, vec_b, inverse);
        constexpr double PI = std::acos(-1.0);
        const double omega = -2.0 * PI / sz_vec * (inverse ? -1.0 : 1.0);
        for (int i = 0; i < sz_vec; i++) {
            int idx = i;
            if (idx >= (sz_vec >> 1)) idx -= sz_vec >> 1;
            vec[i] = vec_a[idx] + Comprex::polar(omega * i) * vec_b[idx];
        }
    };
    dft(dft, ca), dft(dft, cb);
    for (int i = 0; i < sz; i++) ca[i] *= cb[i];
    dft(dft, ca, true);
    std::vector<double> res(sz);
    for (int i = 0; i < sz; i++) res[i] = ca[i].real / sz;
    return res;
}
