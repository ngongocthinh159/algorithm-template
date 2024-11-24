// segtree point update
// each Node struct must associate with a unique Update struct

template<typename Node, typename Updater>
struct SegTree {
private:
    void _build(int idx, int s, int e) {
        if (s == e) {
            tree[idx] = Node(arr[s]);
            return;
        }
        int m = (s + e)/2;
        _build(2*idx, s, m);
        _build(2*idx + 1, m + 1, e);
        tree[idx].merge(tree[2*idx], tree[2*idx + 1]);
    }
    void _update(int idx, int s, int e, int update_idx, Updater &updater) {
        if (s == e) {
            updater.apply(tree[idx]);
            return;
        }
        int m = (s + e)/2;
        if (update_idx <= m) _update(2*idx, s, m, update_idx, updater);
        else _update(2*idx + 1, m + 1, e, update_idx, updater);
        tree[idx].merge(tree[2*idx], tree[2*idx + 1]);
    }
    Node _query(int idx, int s, int e, int l, int r) {
        if (s > r || e < l) return Node();
        if (l <= s && e <= r) return tree[idx];
        int m = (s + e)/2;
        Node l_ans, r_ans, ans;
        l_ans = _query(2*idx, s, m, l, r);
        r_ans = _query(2*idx + 1, m + 1, e, l, r);
        ans.merge(l_ans, r_ans);
        return ans;
    }
public:
    vector<Node> tree;
    int tree_size; // if n is power of 2 => 2*n, otherwise 4*n
    vector<ll> arr; // might change type
    int n;
    SegTree(int _n, vector<ll> &_arr) { // might change type
        arr = _arr;
        n = _n;
        tree_size = !(n&(n - 1)) ? 2*n : 4*n;
        tree.assign(tree_size, Node());
        _build(1, 0, n - 1);
    }
    void update(int idx, int val) {
        Updater updater = Updater(val);
        _update(1, 0, n - 1, idx, updater);
    }
    Node query(int l, int r) {
        return _query(1, 0, n - 1, l, r);
    }
    void print() {
        int siz = (int)tree.size();
        cout << "Printing seg tree " << endl;
        for(int i = 1; i < siz; i++) {
            cout << tree[i].val << " ";
            if(__builtin_popcount(i + 1) == 1) cout << endl;
        }
    }
};
// ***NOTE: each Node struct must associate with a unique Update struct
struct Node {
    ll val;
    Node() {
        val = 0; // might change  (default value, used in query segment out of range)
    }
    Node(ll _val) {
        val = _val; // might change
    }
    void merge(Node &l, Node &r) { // merge two child nodes
        val = l.val + r.val; // might change  (merge logic)
    }
};
struct Updater {
    ll val; // might change  (info required to update segtree node)
    Updater(ll _value_to_update) { // pass in information require to update segtree node
        val = _value_to_update; // might change  (save info)
    }
    void apply(Node &node) { // update logic
        node.val = val;
    }
};
