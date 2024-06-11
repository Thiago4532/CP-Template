#include <bits/stdc++.h>

// Template (thiagomm) {{{
#define ff first
#define ss second
#define mp make_pair
#define fast_io do { ios::sync_with_stdio(false); cin.tie(0); } while(0)
#ifdef TDEBUG
#define debug(...) dout(#__VA_ARGS__, __VA_ARGS__)
#define cdeb cerr
#define dfast_io do {} while(0)
#else
#define debug(...) do {} while(0)
struct dostream {} cdeb;
#define dfast_io fast_io
template<typename T>
dostream& operator<<(dostream& out, T&& t) { return out; }
#endif

template<typename T>
void dout(std::string const& name, T arg) { std::cerr << name << " = " << arg << std::endl; }
template<typename T1, typename... T2>
void dout(std::string const& names, T1 arg, T2... args) {
    std::cerr << names.substr(0, names.find(',')) << " = " << arg << " | ";
    dout(names.substr(names.find(',') + 2), args...);
}

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

template<typename A, typename B>
ostream& operator<<(ostream& out, pair<A, B> const& p) { out << "(" << p.ff << ", " << p.ss << ")"; return out; }
template<typename T>
ostream& operator<<(ostream& out, vector<T> const& v) { for (auto const& e : v) out << e << " "; return out; }
template<typename T>
ostream& operator<<(ostream& out, pair<T*,int> p) { for (;p.ss--;p.ff++) out << *p.ff << " "; return out; }

template<typename T>
void vecinit(int n, vector<T>& v) { v.clear(); v.resize(n + 10); }
template<typename T, typename... Args>
void vecinit(int n, vector<T>& v, vector<Args>&... args) { vecinit(n, v); vecinit(n, args...); }
template<typename T, typename U>
void vecinitN(int n, const U& x, vector<T>& v) { v.assign(n + 10, x); }
template<typename T, typename U, typename... Args>
void vecinitN(int n, const U& x, vector<T>& v, vector<Args>&... args) { vecinitN(n, x, v); vecinitN(n, x, args...); }

template<typename T>
constexpr T mul_identity(T*) { return T(1); }
template<typename T>
constexpr T mul_identity() { return mul_identity(static_cast<T*>(0)); }

template<typename T>
constexpr T pot(T a, int e) {
    T r = mul_identity<T>();
    while (e) {
        if (e%2) r *= a;
        a *= a;
        e /= 2;
    }
    return r;
}

template<int MOD, typename T>
constexpr T pot(T a, int e) {
    T r = mul_identity<T>();
    while (e) {
        if (e%2) r = (r * a) % MOD;
        a = (a * a)%MOD;
        e /= 2;
    }
    return r;
}

// }}}
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

const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;

int main() { dfast_io;
    // Print the first 15 elements of the fibonacci sequence
    // 0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377

    mat<2, 2> fib({0, 1, 1, 1});
    for (int i = 0; i < 15; i++)
        cout << "fib(" << i << "): " << pot(fib, i)(1, 0) << "\n";

    return 0;
}
