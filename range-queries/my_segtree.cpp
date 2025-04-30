// T: the data type 1 that stored in the Node, might change
// T also used for update query in this implementation
template <typename Node, typename T>
struct SegmentTree {
    int n;
    vector<Node> segtree;

    void build(int idx, int s, int e, ll defaultValue) {
        if (s == e) {
            segtree[idx] = Node(defaultValue);
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, defaultValue);
        build(2*idx, m + 1, e, defaultValue);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    void build(int idx, int s, int e, vector<T>& arr) {
        if (s == e) {
            segtree[idx] = Node(arr[s]);
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx, m + 1, e, arr);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    void build(int idx, int s, int e, T *arr) {
        if (s == e) {
            segtree[idx] = Node(arr[s]);
            return;
        }
        int m = (s + e)/2;
        build(2*idx, s, m, arr);
        build(2*idx, m + 1, e, arr);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    void push_down(int idx, int s, int e) {
        if (segtree[idx].lazyType != Node::EMPTY) {
            int m = (s + e)/2;
            segtree[2*idx].apply(s, m, segtree[idx].lazyVal, segtree[idx].lazyType);
            segtree[2*idx + 1].apply(m + 1, e, segtree[idx].lazyVal, segtree[idx].lazyType);
            segtree[idx].clearLazy();
        }
    }

    void update(int idx, int s, int e, int l, int r, T updateVal, typename Node::LazyType lazyType) {
        if (s > r || l > e || s > e || l > r) return;
        if (l <= s && e <= r) {
            segtree[idx].apply(s, e, updateVal, lazyType);
            return;
        }
        push_down(idx, s, e);
        int m = (s + e)/2;
        update(2*idx, s, m, l, r, updateVal, lazyType);
        update(2*idx + 1, m + 1, e, l, r, updateVal, lazyType);
        segtree[idx] = Node::merge(segtree[2*idx], segtree[2*idx + 1]);
    }

    Node query(int idx, int s, int e, int l, int r) {
        if (s > r || l > e || s > e || l > r) 
            return Node::sentinal_query_value();
        if (l <= s && e <= r) 
            return segtree[idx];
        push_down(idx, s, e);
        int m = (s + e)/2;
        Node lans = query(2*idx, s, m, l, r);
        Node rans = query(2*idx + 1, m + 1, e, l, r);
        return Node::merge(lans, rans);
    }
public:
    SegmentTree() {}

    SegmentTree(int _n, ll defaultValue = 0) : n(_n) {
        segtree.resize((n&(n - 1)) == 0 ? 2 * n : 4 * n);
        if (defaultValue)
            build(1, 0, n - 1, defaultValue);
    }

    SegmentTree(vector<T>& arr) {
        n = arr.size();
        segtree.resize((n&(n - 1)) == 0 ? 2 * n : 4 * n);
        build(1, 0, n - 1, arr);
    }

    SegmentTree(int _n, T *arr) : n(_n) {
        segtree.resize((n&(n - 1)) == 0 ? 2 * n : 4 * n);
        build(1, 0, n - 1, arr);
    }

    void update(int l, int r, T updateVal, typename Node::LazyType lazyType) {
        update(1, 0, n - 1, l, r, updateVal, lazyType);
    }

    Node query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

struct Node {
    enum LazyType { EMPTY, PLUS }; // update type might change

    // Type 1 data might change
    ll sum = 0;

    // Type 2 data might change
    LazyType lazyType = EMPTY;
    ll lazyVal = 0;

    Node() {}

    // constructor for type 1 data might change
    Node(ll x) {
        sum = x;
    }

    // push up logic might change
    static Node merge(Node& l, Node& r) {
        Node res;
        res.sum = l.sum + r.sum;
        return res;
    }

    // default value when query out of range might change
    static Node sentinal_query_value() {
        Node res;
        res.sum = 0;
        return res;
    }

    // apply range update to current node
    // put a lazy tag on current node (later push down)
    // might change
    void apply(int s, int e, ll updateVal, LazyType _type) {
        if (_type == PLUS) {
            sum += updateVal * (e - s + 1);
            lazyVal += updateVal;
            lazyType = PLUS;
        }
    }

    // clear lazy value after pushing down lazy val from current node
    void clearLazy() {
        lazyType = EMPTY;
        lazyVal = 0;
    }
};
