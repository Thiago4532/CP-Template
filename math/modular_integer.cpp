template<typename T>
T pot(T a, int e) {
    T r = 1;
    while (e) {
        if (e%2) r *= a;

        a *= a;
        e /= 2;
    }
    return r;
}

struct int_m {
    constexpr int_m(): n(0) {}
    constexpr int_m(int n): n(n) {}

    constexpr operator int() const { return n; }
    constexpr int_m to_positive() const { return n + (n < 0 ? mod : 0); }
    constexpr int_m& to_positive() { if (n < 0) n += mod; return *this; }
    constexpr int_m normalize() const { return n%mod; }
    constexpr int_m& normalize() { n %= mod; return *this; }

    int n;
};

int_m operator+(int_m a, int b) { return (a.n + b)%mod; }
int_m operator+(int a, int_m b) { return (a + b.n)%mod; }
int_m operator+(int_m a, int_m b) { return (a.n + b.n)%mod; }
int_m& operator+=(int_m& a, int b) { a.n += b; a.n %= mod; return a; }
int_m operator-(int_m a, int b) { return (a.n - b)%mod; }
int_m operator-(int a, int_m b) { return (a - b.n)%mod; }
int_m operator-(int_m a, int_m b) { return (a.n - b.n)%mod; }
int_m& operator-=(int_m& a, int b) { a.n -= b; a.n %= mod; return a; }
int_m operator*(int_m a, int b) { return (a.n * b)%mod; }
int_m operator*(int a, int_m b) { return (a * b.n)%mod; }
int_m operator*(int_m a, int_m b) { return (a.n * b.n)%mod; }
int_m& operator*=(int_m& a, int b) { a.n *= b; a.n %= mod; return a; }

int_m inv(int_m x) { return pot(x, mod - 2); }

int_m operator/(int_m a, int b) { return a * inv(b); }
int_m operator/(int a, int_m b) { return a * inv(b); }
int_m operator/(int_m a, int_m b) { return a * inv(b); }
int_m& operator/=(int_m& a, int b) { return a *= inv(b); }
