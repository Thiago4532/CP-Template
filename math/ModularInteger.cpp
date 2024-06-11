// Modular Integer (thiagomm) {{{
// Dependencies: base, mod (constant)

struct int_m {
    constexpr int_m(): n(0) {}
    constexpr int_m(int n): n(n) {}

    constexpr operator int() const { return n; }
    constexpr int_m as_positive() const { return n + (n < 0 ? mod : 0); }
    constexpr int_m& to_positive() { if (n < 0) n += mod; return *this; }
    constexpr int_m normalized() const { return n%mod; }
    constexpr int_m& normalize() { n %= mod; return *this; }

    int n;
};

constexpr int_m operator+(int_m a, int b) { return (a.n + b)%mod; }
constexpr int_m operator+(int a, int_m b) { return (a + b.n)%mod; }
constexpr int_m operator+(int_m a, int_m b) { return (a.n + b.n)%mod; }
constexpr int_m& operator+=(int_m& a, int b) { a.n += b; a.n %= mod; return a; }
constexpr int_m operator-(int_m a, int b) { return (a.n - b)%mod; }
constexpr int_m operator-(int a, int_m b) { return (a - b.n)%mod; }
constexpr int_m operator-(int_m a, int_m b) { return (a.n - b.n)%mod; }
constexpr int_m& operator-=(int_m& a, int b) { a.n -= b; a.n %= mod; return a; }
constexpr int_m operator*(int_m a, int b) { return (a.n * b)%mod; }
constexpr int_m operator*(int a, int_m b) { return (a * b.n)%mod; }
constexpr int_m operator*(int_m a, int_m b) { return (a.n * b.n)%mod; }
constexpr int_m& operator*=(int_m& a, int b) { a.n *= b; a.n %= mod; return a; }

constexpr int_m inv(int_m x) { return pot<mod>(x, mod - 2); }

constexpr int_m operator/(int_m a, int b) { return a * inv(b); }
constexpr int_m operator/(int a, int_m b) { return a * inv(b); }
constexpr int_m operator/(int_m a, int_m b) { return a * inv(b); }
constexpr int_m& operator/=(int_m& a, int b) { return a *= inv(b); }

// }}}
