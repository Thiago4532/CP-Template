// Lazy Segment Tree (thiagomm) {{{
// Dependencies: vector
// WARNING: REALLY BAD API FIX THIS

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

template<typename T, typename U>
class LazyT {
public:
    inline T& node() {
        return tree[seg];
    }

    inline T& lazy() {
        return lazytree[seg];
    }

    inline LazyT l() { return LazyT(tree, lazytree, 2*seg, ini_, (ini_ + fim_)/2); }
    inline LazyT r() { return LazyT(tree, lazytree, 2*seg + 1, (ini_ + fim_)/2 + 1, fim_); }

    inline bool is_leaf() const {
        return (ini_ == fim_);
    }

    template<typename F>
    inline void update_child(F&& setter) {
        if (!is_leaf()) {
            setter(lazytree[2*seg], lazy());
            setter(lazytree[2*seg + 1], lazy());
        }
    }

    inline int ini() const { return ini_; }
    inline int fim() const { return fim_; }
    inline int size() const { return fim_ - ini_ + 1; }

private:
    LazyT(vector<T>& tree, vector<U>& lazytree, int seg, int ini, int fim):
        tree(tree), lazytree(lazytree), seg(seg), ini_(ini), fim_(fim) { }

    template<typename T2, typename U2, auto Merge, auto Flush>
    friend class LazySegTree;

    vector<T>& tree;
    vector<U>& lazytree;
    int seg, ini_, fim_;
};

namespace segutil {

template<typename T, typename U>
void adl_flush(LazyT<T, U> node) {
    do_flush(node);
}

}

template<typename T, typename U,
    auto Merge = segutil::adl_merge<T>,
    auto Flush = segutil::adl_flush<T, U>>
class LazySegTree {
public:
    LazySegTree() = default;
    LazySegTree(int n) : n(n), tree(4*n + 10), lazy(4*n + 10) { }

    void init(int n) {
        this->n = n;
        tree.clear();
        tree.resize(4*n + 10);
        lazy.clear();
        lazy.resize(4*n + 10);
    }

    void init(int n, T const& v, T const& u) {
        this->n = n;
        tree.assign(4*n + 10, v);
        lazy.assign(4*n + 10, u);
    }

    template<typename F>
    void build(int n, F&& getter) {
        init(n);
        return build(getter, 1, 1, n);
    }

    void update(int l, int r, T const& v) {
        return update(l, r, v, 1, 1, n);
    }

    void update_p(int p, T const& v) {
        return update_p(p, v, 1, 1, n);
    }

    T query(int l, int r) {
        return query(l, r, 1, 1, n);
    }

private:
    void flush(int seg, int ini, int fim) {
        return Flush(LazyT(tree, lazy, seg, ini, fim));
    }

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

    void update(int l, int r, T const& v, int seg, int ini, int fim) {
        flush(seg, ini, fim);
        if (l <= ini && fim <= r) {
            lazy[seg] = v;
            flush(seg, ini, fim);
            return;
        }

        int meio = (ini + fim) / 2;
        int L = 2 * seg, R = 2 * seg + 1;

        if (r <= meio) {
            update(l, r, v, L, ini, meio);
            flush(R, meio+1, fim);
        } else if (l > meio) {
            update(l, r, v, R, meio + 1, fim);
            flush(L, ini, meio);
        } else {
            update(l, r, v, L, ini, meio);
            update(l, r, v, R, meio + 1, fim);
        }

        tree[seg] = Merge(tree[L], tree[R]);
    }

    void update_p(int p, T const& v, int seg, int ini, int fim) {
        flush(seg, ini, fim);
        if (ini == fim) {
            tree[seg] = v;
            return;
        }

        int meio = (ini + fim) / 2;
        int L = 2 * seg, R = 2 * seg + 1;

        if (p <= meio) {
            update_p(p, v, L, ini, meio);
            flush(R, meio+1, fim);
        } else {
            update_p(p, v, R, meio + 1, fim);
            flush(L, ini, meio);
        }

        tree[seg] = Merge(tree[L], tree[R]);
    }

    T query(int l, int r, int seg, int ini, int fim) {
        flush(seg, ini, fim);
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
    vector<U> lazy;
    int n;
};

// }}}
