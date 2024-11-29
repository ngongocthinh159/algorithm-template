// references: https://usaco.guide/plat/RURQ?lang=cpp



#define MAX 100005


enum LazyType { ADD, SET, NONE };
struct Data {
    ll sum;
};
struct Lazy {
    LazyType type = NONE;
    ll val = 0;
};
Data segtree[4*MAX];
Lazy lazy[4*MAX];
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
        segtree[idx] = make_data(0);
        return;
    }
    int m = (s + e)/2;
    build(2*idx, s, m);
    build(2*idx + 1, m + 1, e);
    segtree[idx] = merge(segtree[2*idx], segtree[2*idx + 1]);
}
void apply(int idx, int s, int e, const Lazy &operation) {
    if (operation.type == ADD) {
        segtree[idx].sum += operation.val*(e - s + 1);
        if (lazy[idx].type == NONE) {
            lazy[idx] = operation;
        } else if (lazy[idx].type == ADD || lazy[idx].type == SET) {
            lazy[idx].val += operation.val;
        }
    } else if (operation.type == SET) {
        segtree[idx].sum = operation.val*(e - s + 1);
        if (lazy[idx].type == NONE) {
            lazy[idx] = operation;
        } else if (lazy[idx].type == ADD) {
            lazy[idx].type = SET;
            lazy[idx].val = operation.val;
        } else if (lazy[idx].type == SET) {
            lazy[idx].val = operation.val;
        }
    }
};
void push_down(int idx, int s, int e) {
    int m = (s + e)/2;
    apply(2*idx, s, m, lazy[idx]); // apply left child
    apply(2*idx + 1, m + 1, e, lazy[idx]); // apply right child
    lazy[idx] = Lazy(); // reset lazy
}
void update(int idx, int s, int e, int l, int r, const Lazy &operation) { // range update + val
    if (s > r || e < l) return;
    if (l <= s && e <= r) {
        apply(idx, s, e, operation);
        return;
    }
    push_down(idx, s, e);
    int m = (s + e)/2;
    update(2*idx, s, m, l, r, operation);
    update(2*idx + 1, m + 1, e, l, r, operation);
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
void pre_compute() {

}
int n, m;
void solve() {
    cin >> n >> m;
    int t, l, r, pos, val;
    for (int i = 0; i < m; i++) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> val;
            r--;
            update(1, 0, n - 1, l, r, Lazy({SET, val}));
        } else if (t == 2) {
            cin >> l >> r >> val;
            r--;
            update(1, 0, n - 1, l, r, Lazy({ADD, val}));
        } else {
            cin >> l >> r;
            r--;
            cout << query(1, 0, n - 1, l, r).sum << nline;
        }
    }
}
