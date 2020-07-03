#include <bits/stdc++.h>

template <typename T>
class Matrix {
private:
    int H, W;
    std::valarray<T> mat;

public:
    Matrix() noexcept : H(0), W(0) {}
    Matrix(int H, int W, T a = T()) noexcept : H(H), W(W), mat(a, H * W) {}

    void set_size(int H, int W, T a = T()) noexcept {
        this->H = H;
        this->W = W;
        mat = std::valarray<T>(a, H * W);
    }

    const T& operator()(int i, int j) const noexcept {
        return mat[i + j * H];
    }
    T& operator()(int i, int j) noexcept {
        return mat[i + j * H];
    }

    Matrix& operator+=(const Matrix& r) noexcept {
        mat += r.mat;
        return *this;
    }
    Matrix& operator-=(const Matrix& r) noexcept {
        mat -= r.mat;
        return *this;
    }
    Matrix& operator*=(const Matrix& r) noexcept {
        *this = *this * r;
        return *this;
    }

    friend Matrix operator+(const Matrix& l, const Matrix& r) noexcept {
        return Matrix(l) += r;
    }
    friend Matrix operator-(const Matrix& l, const Matrix& r) noexcept {
        return Matrix(l) -= r;
    }
    friend Matrix operator*(const Matrix& l, const Matrix& r) noexcept {
        Matrix res(l.H, r.W);
        const int C = std::max(l.W, r.H);
        for (int i = 0; i < l.H; i++) {
            auto t = l.mat[std::slice(i, C, l.H)];
            for (int j = 0; j < r.W; j++) {
                res(i, j) = (t * r.mat[std::slice(j * r.H, C, 1)]).sum();
            }
        }
        return res;
    }
    friend Matrix operator*(const T& l, const Matrix& r) noexcept {
        Matrix res(r);
        res.mat *= l;
        return res;
    }
    friend Matrix operator*(const Matrix& l, const T& r) noexcept {
        Matrix res(l);
        res.mat *= r;
        return res;
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix& r) {
        for (int i = 0; i < r.H; i++) {
            for (int j = 0; j < r.W; j++) {
                os << r(i, j) << " ";
            }
            if (i != r.H - 1) {
                os << "\n";
            }
        }
        return os;
    }
};