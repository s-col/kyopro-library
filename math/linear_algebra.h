#include <bits/stdc++.h>

#include "kyopro-library/mod/ModInt.h"

template <typename T>
class Matrix {
protected:
    int H, W;
    std::valarray<T> mat;

public:
    Matrix() noexcept : H(0), W(0) {}
    Matrix(int H, int W = 1, T a = T(0)) noexcept : H(H), W(W), mat(a, H * W) {}
    Matrix(std::initializer_list<T> list) noexcept : H(list.size()), W(1), mat(list) {}
    void resize(int H, int W, T a = T(0)) noexcept {
        if (H * W > this->H * this->W) {
            this->mat.resize(H * W, a);
        }
        this->H = H;
        this->W = W;
    }
    std::pair<int, int> size() const noexcept { return {H, W}; }
    int len() const noexcept { return H * W; }
    int row() const noexcept { return H; }
    int col() const noexcept { return W; }
    const T& operator()(int i) const noexcept {
        return mat[i];
    }
    T& operator()(int i) noexcept {
        return mat[i];
    }
    const T& operator()(int i, int j) const noexcept {
        return mat[i * W + j];
    }
    T& operator()(int i, int j) noexcept {
        return mat[i * W + j];
    }
    Matrix& operator=(std::initializer_list<T> list) noexcept {
        assert(H * W == static_cast<int>(list.size()));
        mat = list;
        return *this;
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
            for (int k = 0; k < C; k++) {
                const T t = l(i, k);
                for (int j = 0; j < r.W; j++) {
                    res(i, j) += t * r(k, j);
                }
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

// solve a linear equation: Ax = b, by Gaussian elimination
template <typename T>
std::optional<Matrix<T>> solve_leq(const Matrix<T>& A, const Matrix<T>& b, T eps) {
    assert(A.row() == b.row() && b.col() == 1);
    auto [H, W] = A.size();
    Matrix<T> mat(H, W + 1);  // extended matrix
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) mat(i, j) = A(i, j);
        mat(i, W) = b(i);
    }
    // Gaussian elimination
    int rank = 0;
    std::vector<int> p(H);
    std::vector<int> is_pivot(W, false);
    std::iota(p.begin(), p.end(), 0);
    for (int j = 0; j < W; j++) {
        int pivot = -1;
        T mx = eps;
        for (int i = rank; i < H; i++) {
            const int row = p[i];
            if (std::abs(mat(row, j)) > mx) pivot = i, mx = std::abs(mat(row, j));
        }
        if (pivot == -1) continue;
        is_pivot[j] = true;
        std::swap(p[rank], p[pivot]);
        const int r_pivot = p[rank];
        const T fac = T(1) / mat(r_pivot, j);
        for (int k = 0; k <= W; k++) mat(r_pivot, k) *= fac;
        for (int i = 0; i < H; i++) {
            const int row = p[i];
            if (i != rank && std::abs(mat(row, j)) > eps) {
                const T fac = mat(row, j);
                for (int k = 0; k <= W; k++) mat(row, k) -= mat(r_pivot, k) * fac;
            }
        }
        ++rank;
    }
    // Determine the existence of a solution
    for (int i = rank; i < H; i++)
        if (std::abs(mat(p[i], W)) > eps) return std::nullopt;
    // solve the equation
    Matrix<T> res(W, 1, 0);
    int cur = 0;
    for (int i = 0; i < W; i++)
        if (is_pivot[i]) res(i) = mat(p[cur++], W);
    return res;
}

// solve a linear equation: Ax = b, by Gaussian elimination
// specialization for ModInt
template <int_fast64_t MOD>
std::optional<Matrix<ModInt<MOD>>> solve_leq(const Matrix<ModInt<MOD>>& A, const Matrix<ModInt<MOD>>& b) {
    assert(A.row() == b.row() && b.col() == 1);
    auto [H, W] = A.size();
    Matrix<ModInt<MOD>> mat(H, W + 1);  // extended matrix
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) mat(i, j) = A(i, j);
        mat(i, W) = b(i);
    }
    // Gaussian elimination
    int rank = 0;
    std::vector<int> p(H);
    std::vector<int> is_pivot(W, false);
    std::iota(p.begin(), p.end(), 0);
    for (int j = 0; j < W; j++) {
        int pivot = -1;
        for (int i = rank; i < H; i++)
            if (mat(p[i], j) != 0) {
                pivot = i;
                break;
            }
        if (pivot == -1) continue;
        is_pivot[j] = true;
        std::swap(p[rank], p[pivot]);
        const int r_pivot = p[rank];
        const ModInt<MOD> fac = mat(r_pivot, j).inv();
        for (int k = 0; k <= W; k++) mat(r_pivot, k) *= fac;
        for (int i = 0; i < H; i++) {
            const int row = p[i];
            if (i != rank && mat(row, j) != 0) {
                const ModInt<MOD> fac = mat(row, j);
                for (int k = 0; k <= W; k++) mat(row, k) -= mat(r_pivot, k) * fac;
            }
        }
        ++rank;
    }
    // Determine the existence of a solution
    for (int i = rank; i < H; i++)
        if (mat(p[i], W) != 0) return std::nullopt;
    // solve the equation
    Matrix<ModInt<MOD>> res(W, 1, 0);
    int cur = 0;
    for (int i = 0; i < W; i++)
        if (is_pivot[i]) res(i) = mat(p[cur++], W);
    return res;
}