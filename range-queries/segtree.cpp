// segtree point update
// each Node struct must associate with a unique Update struct

template<typename Node, typename Update>
struct SegTree {
private:
    vector<Node> tree;
    int tree_size; // if n is power of 2 => 2*n, otherwise 4*n
    vector<ll> arr; // might change type
    
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
    void _update(int idx, int s, int e, int update_idx, Update &update_obj) {
        if (s == e) {
            update_obj.apply(tree[idx]);
            return;
        }
        int m = (s + e)/2;
        if (update_idx <= m) update(2*idx, s, m, update_idx, u);
        else update(2*idx + 1, m + 1, e, update_idx, u);
        tree[idx].merge(tree[2*idx], tree[2*idx + 1]);
    }
    Node _query(int idx, int s, int e, int l, int r) {
        if (s > r || r < l) return Node();
        if (l <= s && e <= r) return tree[idx];
        int m = (s + e)/2;
        Node l, r, ans;
        l = _query(2*idx, s, m, l, r);
        r = _query(2*idx + 1, m + 1, e, l, r);
        ans.merge(l, r);
        return ans;
    }
public:
    SegTree(int n, vector<ll> &arr) { // might change type
        this->arr = arr;
        if (!(n&(n - 1))) tree_size = 2*n;
        else tree_size = 4*n;
        tree.assign(tree_size, Node());
        _build(1, 0, n - 1);
    }
    void update(int idx, int val) {
        Update update_obj = Update(val);
        _update(1, 0, n - 1, idx, update_obj);
    }
    Node query(int l, int r) {
        return _query(1, 0, n - 1, l, r);
    }
};
struct Node {
    ll val;
    Node() {
        val = 0; // might change  (default value)
    }
    Node(ll val) {
        val = val; // might change
    }
    void merge(Node &l, Node &r) { // merge two child nodes
        val = l.val + r.val; // might change  (merge logic)
    }
};
struct Update {
    ll val; // might change  (info required to update segtree node)
    Update(ll p1) { // pass in information require to update segtree node
        val = p1; // might change  (save info)
    }
    void apply(Node &node) { // update logic
        node.val = val;
    }
};
