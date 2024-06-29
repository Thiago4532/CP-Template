#include <bits/stdc++.h>

// Template (thiagomm) {{{
#define ff first
#define ss second
#define mp make_pair
#define fast_io do { ios::sync_with_stdio(false); cin.tie(0); } while(0)
#define IFCONST if constexpr
#define all(x) (x).begin(), (x).end()
#ifdef TDEBUG
#define cdeb cerr
#define dfast_io do {} while(0)
#else
struct dostream {} cdeb;
#define dfast_io fast_io
template<typename T>
dostream& operator<<(dostream& out, T&& t) { return out; }
#endif

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
using __int = decltype(0);

template<typename T>
constexpr T __inf_getter() {
    int32_t N = sizeof(T);
    
    T r = 0;
    for (int32_t i = 0; i < N; i++)
        r = (r << 8) | 0x3f;
    return r;
}

template<typename T>
constexpr auto _inf = __inf_getter<T>();
constexpr int inf = _inf<int>;

template<typename A, typename B>
ostream& operator<<(ostream& out, pair<A, B> const& p) { out << "(" << p.ff << ", " << p.ss << ")"; return out; }
template<typename A, typename B>
istream& operator>>(istream& in, pair<A, B>& p) { in >> p.ff >> p.ss; return in; }

template<typename T>
auto operator!(vector<T>& v) { return v.begin(); }
template<typename T>
auto operator!(vector<T> const& v) { return v.begin(); }
template<typename T>
auto operator+(vector<T>& v, ptrdiff_t diff) { return v.begin() + diff; }
template<typename T>
auto operator+(vector<T> const& v, ptrdiff_t diff) { return v.begin() + diff; }
template<typename T>
auto operator-(vector<T>& v, ptrdiff_t diff) { return v.begin() - diff; }
template<typename T>
auto operator-(vector<T> const& v, ptrdiff_t diff) { return v.begin() - diff; }

template<typename T>
void vecinit(int32_t n, vector<T>& v) { v.clear(); v.resize(n + 0); }
template<typename T, typename... Args>
void vecinit(int32_t n, vector<T>& v, vector<Args>&... args) { vecinit(n, v); vecinit(n, args...); }
template<typename T, typename U>
void vecinitN(int32_t n, const U& x, vector<T>& v) { v.assign(n + 0, x); }
template<typename T, typename U, typename... Args>
void vecinitN(int32_t n, const U& x, vector<T>& v, vector<Args>&... args) { vecinitN(n, x, v); vecinitN(n, x, args...); }

template<typename T>
void readArray(T& v, int32_t l, int32_t r) { for (int32_t i = l; i <= r; i++) cin >> v[i]; }

template<typename T>
void printArray(T& v, int32_t l, int32_t r) { for (int32_t i = l; i <= r; i++) cout << v[i] << " \n"[i==r]; }

template<bool directed = false>
void readGraph(vector<int> G[], int32_t m) {
    for (int32_t i = 1; i <= m; i++) {
        int32_t a, b;
        cin >> a >> b;
        G[a].push_back(b);
        IFCONST (!directed) G[b].push_back(a);
    }
}

template<bool directed = false>
void readGraphW(vector<pii> G[], int32_t m) {
    for (int i = 1; i <= m; i++) {
        int32_t a, b, c;
        cin >> a >> b >> c;
        G[a].push_back({b, c});
        IFCONST (!directed) G[b].push_back({a, c});
    }
}

template<typename Function, typename... Args>
void runAndPrint(Function&& f, Args&&... args) {
    using ret_t = decltype(f(std::forward<Args>(args)...));
    IFCONST (std::is_same_v<ret_t, void>)
        f(std::forward<Args>(args)...);
    else IFCONST(std::is_same_v<ret_t, bool>)
        cout << (f(std::forward<Args>(args)...) ? "YES\n" : "NO\n");
    else
        cout << f(std::forward<Args>(args)...) << "\n";
}

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

template<typename T>
constexpr int clz(T x) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    static_assert(sizeof(T) <= sizeof(ull));

    auto y = static_cast<make_unsigned_t<T>>(x);
    IFCONST (sizeof(T) <= sizeof(__int)) {
        __int d = sizeof(__int) - sizeof(T);
        return __builtin_clz(y) - d;
    } else {
        __int d = sizeof(ull) - sizeof(T);
        return __builtin_clzll(y) - d;
    }
}

template<typename T>
constexpr int msb(T x) {
    constexpr int nbits = 8*sizeof(T);
    return nbits - 1 - clz(x);
}

// }}}
// Segment Tree (thiagomm) {{{
// Dependencies: vector

// Segment Tree Utils {{{
#ifndef _TMM_SEGUTIL
#define _TMM_SEGUTIL
namespace segutil {

template<typename T>
T adl_merge(T const& a, T const& b) { return merge(a, b); }
template<typename T>
T const& min(T const& a, T const& b) { return std::min(a, b); }
template<typename T>
T const& max(T const& a, T const& b) { return std::max(a, b); }
template<typename T>
T sum(T const& a, T const& b) { return a + b; }
template<typename T>
T mul(T const& a, T const& b) { return a * b; }
template<typename T>
void assign(T& a, T const& b) { a = b; }
template<typename T>
void add(T& a, T const& b) { return a += b; }

template<typename T, typename U>
void updater(T& a, U const& b) { a = b; } // default updater
template<typename T>
void adl_updater(T& a, T const& b) { updater(a, b); }
#endif

}
// }}}
// Function wrapper {{{
#ifndef _TMM_FWRAP
#define _TMM_FWRAP

template<auto F>
struct fwrap {
    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const {
        return F(std::forward<Args>(args)...);
    }
};

#endif
// }}}

template<
    typename T,
    auto Merge = segutil::adl_merge<T>,
    auto Updater = segutil::adl_updater<T>
>
class SegTree {
public:
    SegTree() = default;
    SegTree(int n) : n(n), tree(4*n + 10) { }

    void init(int n) {
        this->n = n;
        tree.clear();
        tree.resize(4*n + 10);
    }

    void init(int n, T const& v) {
        this->n = n;
        tree.assign(4*n + 10, v);
    }

    template<typename F>
    void build(int n, F&& getter) {
        init(n);
        return build(getter, 1, 1, n);
    }

    template<auto __Updater, typename U>
    void update(int p, U const& v) {
        return update<U>(p, v, 1, 1, n, fwrap<__Updater>{});
    }

    template<typename U, typename F>
    void update(int p, U const& v, F&& upd) {
        return update<U>(p, v, 1, 1, n, std::forward<F>(upd));
    }

    void update(int p, T const& v) {
        return update<T>(p, v, 1, 1, n, fwrap<Updater>{});
    }

    T query(int l, int r) const {
        return query(l, r, 1, 1, n);
    }

// private:
    template<typename F>
    void build(F&& getter, int seg, int ini, int fim) {
        if (ini == fim) {
            tree[seg] = getter(ini);
            return;
        }

        int meio = (ini + fim) / 2;
        int L = 2 * seg, R = 2 * seg + 1;
        build(getter, L, ini, meio);
        build(getter, R, meio + 1, fim);
        tree[seg] = Merge(tree[L], tree[R]);
    }

    template<typename U, typename F>
    void update(int p, U const& v, int seg, int ini, int fim, F&& upd) {
        if (ini == fim) {
            upd(tree[seg], v);
            return;
        }

        int meio = (ini + fim) / 2;
        int L = 2 * seg, R = 2 * seg + 1;

        if (p <= meio)
            update<U>(p, v, L, ini, meio, std::forward<F>(upd));
        else
            update<U>(p, v, R, meio + 1, fim, std::forward<F>(upd));
        tree[seg] = Merge(tree[L], tree[R]);
    }

    T query(int l, int r, int seg, int ini, int fim) const {
        if (l <= ini && fim <= r)
            return tree[seg];

        int meio = (ini + fim) / 2;
        int L = 2 * seg, R = 2 * seg + 1;

        if (r <= meio)
            return query(l, r, L, ini, meio);
        if (l > meio)
            return query(l, r, R, meio + 1, fim);

        return Merge(
            query(l, r, L, ini, meio),
            query(l, r, R, meio + 1, fim)
        );
    }
    
    vector<T> tree;
    int n;
};

// }}}

const int maxn = 2e5 + 10;
const int mod = 1e9 + 7;

int main() { dfast_io;
    int n, q;
    cin >> n >> q;
    SegTree<ll, segutil::sum<ll>> seg;
    seg.build(n, [](int i) {
        ll x;
        cin >> x;
        return x;
    }); 
    while(q--) {
        int op;
        cin >> op;
        if (op == 0) {
            int p;
            ll x;
            cin >> p >> x;
            ++p;
            seg.update(p, monostate{}, [&](ll& a, monostate) {
                a += x;
            });
        } else {
            int l, r;
            cin >> l >> r;
            ++l;
            ll x = seg.query(l, r);
            cout << x << "\n";
        }
    }
    return 0;
}
