// Segment Tree (thiagomm) {{{
// Dependencies: vector

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

}

template<typename T, auto Merge = segutil::adl_merge<T>>
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

    void update(int p, T const& v) {
        return update(p, v, 1, 1, n);
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

    void update(int p, T const& v, int seg, int ini, int fim) {
        if (ini == fim) {
            tree[seg] = v;
            return;
        }

        int meio = (ini + fim) / 2;
        int L = 2 * seg, R = 2 * seg + 1;

        if (p <= meio)
            update(p, v, L, ini, meio);
        else
            update(p, v, R, meio + 1, fim);
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
