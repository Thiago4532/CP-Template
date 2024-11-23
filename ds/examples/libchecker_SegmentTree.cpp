#include <bits/stdc++.h>

// Template (thiagomm) {{{
#ifdef TDEBUG
#include "tdebug.hpp"
#define cdeb cerr
#define dfast_io do {} while(0)
#else
#define tdeb_test_begin(i) do {} while(0)
#define tdeb_test_end(i) do {} while(0)
struct dostream {} cdeb;
#define dfast_io fast_io
template<typename T>
dostream& operator<<(dostream& out, T&& t) { return out; }
#endif
#define ff first
#define ss second
#define mp make_pair
#define fast_io do { ios::sync_with_stdio(false); cin.tie(0); } while(0)
#define IFCONST if constexpr
#define all(x) (x).begin(), (x).end()

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
using __int = decltype(0);

mt19937 rng(random_device{}());

int rnd(int a, int b) {
    return rng() % (b - a + 1) + a;
}

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

template<auto F>
struct fwrap {
    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const { return F(std::forward<Args>(args)...); }
};

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

template<typename T, typename... Args>
const T& min(const T& a, const T& b, const T& c, const Args&... args) { return min(a, min(b, c, args...)); }
template<typename T, typename... Args>
const T& max(const T& a, const T& b, const T& c, const Args&... args) { return max(a, max(b, c, args...)); }

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

template<typename T>
void cprint(T const& t) {
    using type = remove_cv_t<remove_reference_t<T>>;
    IFCONST (is_same_v<type, bool>) {
        cout << (t ? "YES" : "NO");
    } else {
        cout << t;
    }
}

template<typename T, typename... Args>
void cprint(T const& t, Args const&... args) {
    cprint(t);
    cprint(args...);
}

template<typename... Args>
void cprintln(Args const&... args) {
    return cprint(args..., '\n');
}

template<typename Function, typename... Args>
decltype(auto) runAndPrint(Function&& f, Args&&... args) {
    using ret_t = decltype(f(std::forward<Args>(args)...));
    IFCONST (is_same_v<ret_t, void>) {
        f(std::forward<Args>(args)...);
    } else {
        ret_t t = f(std::forward<Args>(args)...);
        cprintln(t);
        return t;
    }
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

// Workaround to #define int ll
constexpr int pot(__int a, int e) { return pot(static_cast<int>(a), e); }
template<int MOD>
constexpr int pot(__int a, int e) { return pot<MOD>(static_cast<int>(a), e); }

template<typename T>
constexpr int clz(T x) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    static_assert(sizeof(T) <= sizeof(ll));

    auto y = static_cast<make_unsigned_t<T>>(x);
    IFCONST (sizeof(T) <= sizeof(__int)) {
        __int d = sizeof(__int) - sizeof(T);
        return __builtin_clz(y) - d;
    } else {
        __int d = sizeof(ll) - sizeof(T);
        return __builtin_clzll(y) - d;
    }
}

template<typename T>
constexpr int popcount(T x) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    static_assert(sizeof(T) <= sizeof(ll));

    auto y = static_cast<make_unsigned_t<T>>(x);
    IFCONST (sizeof(T) <= sizeof(__int)) {
        return __builtin_popcount(y);
    } else {
        return __builtin_popcountll(y);
    }
}

template<typename T>
constexpr int msb(T x) {
    constexpr int nbits = 8*sizeof(T);
    return nbits - 1 - clz(x);
}

template<typename T>
string as_binary(T x, int n) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    auto y = static_cast<make_unsigned_t<T>>(x);
    auto b = static_cast<make_unsigned_t<T>>(1);

    string r;
    for (auto i = n - 1; i >= 0; i--)
        r += (y & (b << i) ? '1' : '0');
    return r;
}

template<typename T>
string as_rbinary(T x, int n) {
    static_assert(std::is_integral_v<T>, "T must be an integral type");
    auto y = static_cast<make_unsigned_t<T>>(x);
    auto b = static_cast<make_unsigned_t<T>>(1);

    string r;
    for (auto i = 0; i < n; i++)
        r += (y & (b << i) ? '1' : '0');
    return r;
}

template<typename T>
string as_binary(T x) {
    return x == 0 ? "0" : as_binary(x, 1 + msb(x));
}

template<typename T>
string as_rbinary(T x) {
    return x == 0 ? "0" : as_rbinary(x, 1 + msb(x));
}

// }}}
// Segment Tree (thiagomm) {{{
// Dependencies: vector

// Segment Tree Utils {{{
#ifndef _TMM_SEGUTIL
#define _TMM_SEGUTIL
namespace segu {

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
void add(T& a, T const& b) { a += b; }

template<typename T, typename U>
void updater(T& a, U const& b) { a = b; } // default updater
template<typename T>
void adl_updater(T& a, T const& b) { updater(a, b); }

#endif

}
// }}}

template<
    typename T,
    auto Merge = segu::adl_merge<T>,
    auto Updater = segu::adl_updater<T>
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
        return build(getter, root());
    }

    template<typename U>
    void update(int p, U const& v) {
        auto f = [&v](T& t) { Updater(t, v); };
        return update(p, f, root());
    }

    template<typename F>
    void update2(int p, F&& upd) {
        return update(p, upd, root());
    }

    T query(int l, int r) const {
        return query(l, r, root());
    }

    T get(int p) const {
        node_index index = get(p, root());
        return tree[*index];
    }

// private:
    struct node_index {
        int index;
        int ini, fim;
        int meio() const { return ini + (fim - ini)/2; }

        bool is_leaf() const { return ini == fim; }

        inline node_index L() const { return node_index {2*index, ini, meio()}; }
        inline node_index R() const { return node_index {2*index+1, meio()+1, fim}; }

        inline int operator*() const { return index; }
        inline node_index operator-() const { return L(); }
        inline node_index operator+() const { return R(); }
        inline int operator--() const { return *L(); }
        inline int operator++() const { return *R(); }
    };
    node_index root() const { return {1, 1, n}; }

    template<typename F>
    void build(F&& getter, node_index seg) {
        if (seg.is_leaf()) {
            tree[*seg] = getter(seg.ini);
            return;
        }

        build(getter, -seg);
        build(getter, +seg);
        tree[*seg] = Merge(tree[--seg], tree[++seg]);
    }

    template<typename F>
    void update(int p, F&& upd, node_index seg) {
        if (seg.is_leaf()) {
            upd(tree[*seg]);
            return;
        }

        if (p <= seg.meio())
            update<F>(p, upd, -seg);
        else
            update<F>(p, upd, +seg);
        tree[*seg] = Merge(tree[--seg], tree[++seg]);
    }

    T query(int l, int r, node_index seg) const {
        if (l <= seg.ini && seg.fim <= r)
            return tree[*seg];

        int meio = seg.meio();
        if (r <= meio)
            return query(l, r, -seg);
        if (l > meio)
            return query(l, r, +seg);

        return Merge(
            query(l, r, -seg),
            query(l, r, +seg)
        );
    }

    node_index get(int p, node_index seg) const {
        if (seg.is_leaf())
            return seg;

        if (p <= seg.meio())
            return get(p, -seg);
        return get(p, +seg);
    }

    vector<T> tree;
    int n;
};

// }}}

const int maxn = 5e5 + 10;
const int mod = 1e9 + 7;

// https://judge.yosupo.jp/problem/point_add_range_sum
void Point_Add_Range_Sum() {
    int n, q;
    cin >> n >> q;
    SegTree<ll, segu::sum<ll>, segu::add<ll>> seg;
    seg.build(n, [&](int i) {
        int x;
        cin >> x;
        return x;
    });

    while(q--) {
        int t;
        cin >> t;

        if (t == 0) {
            int p, x;
            cin >> p >> x;
            ++p;
            seg.update(p, x);
        } else if (t == 1){
            int l, r;
            cin >> l >> r;
            ++l;
            cout << seg.query(l, r) << "\n";
        } else {
            cout << "invalid operation: " << t << endl;
            abort();
        }
    }
}

int main() { dfast_io;
    Point_Add_Range_Sum();
    return 0;
}
