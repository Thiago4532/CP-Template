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

template<auto F>
struct fwrap {
    template<typename... Args>
    constexpr decltype(auto) operator()(Args&&... args) const {
        return F(std::forward<Args>(args)...);
    }
};
#endif

}
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
        return update<U>(p, v, 1, 1, n, segutil::fwrap<__Updater>{});
    }

    template<typename U, typename F>
    void update(int p, U const& v, F&& upd) {
        return update<U>(p, v, 1, 1, n, std::forward<F>(upd));
    }

    void update(int p, T const& v) {
        return update<T>(p, v, 1, 1, n, segutil::fwrap<Updater>{});
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
