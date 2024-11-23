struct node {
    int v = 0, qtd = 1;
} tree[4*maxn];
int lazy[4*maxn];
int n, a[maxn];
 
node merge(node const& a, node const& b) {
    if (a.v == b.v)
        return node {a.v, a.qtd + b.qtd};
    if (a.v < b.v)
        return a;
    return b;
}
 
void build(ARGS(1, n)) {
    lazy[seg] = 0;
    if (ini == fim) {
        tree[seg] = node{};
        return;
    }
 
    build(SL);
    build(SR);
    tree[seg] = merge(tree[L], tree[R]);
}
 
void flush(int seg, int ini, int fim) {
    if (!lazy[seg]) return;
 
    tree[seg].v += lazy[seg];
    if (ini != fim) {
        lazy[L] += lazy[seg];
        lazy[R] += lazy[seg];
    }
    lazy[seg] = 0;
}
 
void update(int l, int r, int v, ARGS(1, n)) {
    flush(seg, ini, fim);
    if (ini > r || fim < l) return;
    if (l <= ini && fim <= r) {
        lazy[seg] += v;
        flush(seg, ini, fim);
        return;
    }
 
    update(l, r, v, SL);
    update(l, r, v, SR);
    tree[seg] = merge(tree[L], tree[R]);
}
