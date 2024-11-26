// segtree + lazy update
// oper 1: add val to all element in range [l, r]
// oper 2: query sum in range [l, r]
struct Data {
    ll sum;
};
Data segtree[4*MAX];
ll lazy[4*MAX];
ll a[MAX];
Data make_data(ll sum) {
    Data res;
    res.sum = sum;
    return res;
}
Data merge(Data &l, Data &r) {
    Data res;
    res.sum = l.sum + r.sum;
    return res;
}
void build(int idx, int s, int e) {
    if (s == e) {
        segtree[idx] = make_data(a[s]);
        return;
    }
    int m = (s + e)/2;
    build(2*idx, s, m);
    build(2*idx + 1, m + 1, e);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
void apply(int idx, int s, int e, ll val) {
    segtree[idx].sum += val*(e - s + 1); // apply update
    lazy[idx] += val; // put tag
};
void push_down(int idx, int s, int e) {
    int m = (s + e)/2;
    apply(2*idx, s, m, lazy[idx]); // apply left child
    apply(2*idx + 1, m + 1, e, lazy[idx]); // apply right child
    lazy[idx] = 0; // reset lazy
}
void update(int idx, int s, int e, int l, int r, ll val) { // range update + val
    if (s > r || e < l) return;
    if (l <= s && e <= r) {
        apply(idx, s, e, val);
        return;
    }
    push_down(idx, s, e);
    int m = (s + e)/2;
    update(2*idx, s, m, l, r, val);
    update(2*idx + 1, m + 1, e, l, r, val);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
Data query(int idx, int s, int e, int l, int r) { // range sum query
    if (s > r || e < l) return make_data(0);
    if (l <= s && e <= r) return segtree[idx];
    push_down(idx, s, e);
    int m = (s + e)/2;
    Data l_ans = query(2*idx, s, m, l, r);
    Data r_ans = query(2*idx + 1, m + 1, e, l, r);
    return merge(l_ans, r_ans);
}
