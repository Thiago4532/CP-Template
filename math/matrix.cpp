template<int n, int m, class T = int>
struct mat {
    constexpr T& operator()(int i, int j) { return M[i][j]; }
    constexpr T const& operator()(int i, int j) const { return M[i][j]; }

    constexpr int rows() const { return n; }
    constexpr int cols() const { return m; }

    constexpr static mat<n, m, T> id() {
        static_assert(n == m, "Matrix must be a square matrix!");
        mat<n, m, T> res;
        for (int i = 0; i < n; i++) {
            res(i, i) = 1;
        }
        return res;
    }

    T M[n][m] {0};
};

template<int n, int m, class T>
constexpr mat<n, m, T> operator+(mat<n, m, T> const& a, mat<n, m, T> const& b) {
    mat<n, m, T> c;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            c(i, j) = a(i, j) + b(i, j);
        }
    }
    return c;
}

template<int n, int m, class T>
constexpr mat<n, m, T>& operator+=(mat<n, m, T>& a, mat<n, m, T> const& b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a(i, j) += b(i, j);
        }
    }
    return a;
}

template<int n, int m, int l, class T>
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

template<int n, int m, class T>
constexpr mat<n, m, T>& operator*=(mat<n, m, T>& a, mat<m, m, T> const& b) {
    a = a * b;
    return a;
}

template<int n, class T>
constexpr mat<n, n, T> pot(mat<n, n, T> a, int e) {
    mat<n, n, T> r = mat<n, n, T>::id();
    while (e) {
        if (e%2) r *= a;

        e /= 2;
        a *= a;
    }
    return r;
}
