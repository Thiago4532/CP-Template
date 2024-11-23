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
