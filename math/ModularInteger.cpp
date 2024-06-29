// Modular Integer (thiagomm) {{{
// Dependencies: base

template<int MOD>
struct int_m {
    constexpr int_m(): n(0) {}
    constexpr int_m(int n): n(n%MOD) {}

    constexpr operator int() const { return n; }
    constexpr int_m as_positive() const { return n + (n < 0 ? MOD : 0); }
    constexpr int_m& to_positive() { if (n < 0) n += MOD; return *this; }

    friend constexpr int_m operator+(int_m a, int b) { return (a.n + b)%MOD; }
    friend constexpr int_m operator+(int a, int_m b) { return (a + b.n)%MOD; }
    friend constexpr int_m operator+(int_m a, int_m b) { return (a.n + b.n)%MOD; }
    friend constexpr int_m& operator+=(int_m& a, int b) { a.n += b; a.n %= MOD; return a; }
    friend constexpr int_m operator-(int_m a, int b) { return (a.n - b)%MOD; }
    friend constexpr int_m operator-(int a, int_m b) { return (a - b.n)%MOD; }
    friend constexpr int_m operator-(int_m a, int_m b) { return (a.n - b.n)%MOD; }
    friend constexpr int_m& operator-=(int_m& a, int b) { a.n -= b; a.n %= MOD; return a; }
    friend constexpr int_m operator*(int_m a, int b) { return (a.n * b)%MOD; }
    friend constexpr int_m operator*(int a, int_m b) { return (a * b.n)%MOD; }
    friend constexpr int_m operator*(int_m a, int_m b) { return (a.n * b.n)%MOD; }
    friend constexpr int_m& operator*=(int_m& a, int b) { a.n *= b; a.n %= MOD; return a; }

    constexpr int_m inverse() { return pot<MOD>(n, MOD - 2); }

    friend constexpr int_m operator/(int_m a, int_m b) { return a * b.inverse(); }
    friend constexpr int_m& operator/=(int_m& a, int_m b) { return a *= b.inverse(); }


    int n;
};


// }}}
