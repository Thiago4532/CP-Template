// Matrix (thiagomm) {{{

#include <type_traits>

template<int n, int m, typename T = int>
struct mat {
    constexpr T& operator()(int i, int j) { return M[i][j]; }
    constexpr T const& operator()(int i, int j) const { return M[i][j]; }

    static constexpr int rows() { return n; }
    static constexpr int cols() { return m; }

    constexpr static mat<n, m, T> id(typename std::enable_if<n == m>::type* = 0) {
        mat<n, m, T> res;
        for (int i = 0; i < n; i++) {
            res(i, i) = 1;
        }
        return res;
    }

    T M[n][m] {0};
};

template<int n, int m, typename T>
constexpr mat<n, m, T> operator+(mat<n, m, T> const& a, mat<n, m, T> const& b) {
    mat<n, m, T> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c(i, j) = a(i, j) + b(i, j);
        }
    }
    return c;
}

template<int n, int m, typename T>
constexpr mat<n, m, T>& operator+=(mat<n, m, T>& a, mat<n, m, T> const& b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a(i, j) += b(i, j);
        }
    }
    return a;
}

template<int n, int m, int l, typename T>
constexpr mat<n, m, T> operator*(mat<n, l, T> const& a, mat<l, m, T> const& b) {
    mat<n, m, T> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < l; k++) {
                c(i, j) += a(i, k)*b(k, j);
            }
        }
    }
    return c;
}

template<int n, int m, typename T>
constexpr mat<n, m, T>& operator*=(mat<n, m, T>& a, mat<m, m, T> const& b) {
    a = a * b;
    return a;
}

template <int n, typename T>
constexpr mat<n, n, T> mul_identity(mat<n, n, T>*) {
    return mat<n, n, T>::id();
}

// }}}
