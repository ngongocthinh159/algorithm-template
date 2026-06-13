#define BIT 32

struct Node {
    Node* child[2];
    int cnt;
    int leaf;
    Node() {
        child[0] = child[1] = nullptr;
        cnt = 0;
        leaf = 0;
    }
};

struct Trie {
public:
    Trie() {
        root = new Node;
    }
    void insert(int x) {
        insert_dfs(root, x, BIT - 1);
    }
    void remove(int x) {
        remove_dfs(root, x, BIT - 1);
    }
    int queryMex() {
        Node* p = root;
        int res = 0;
        for (int bit = BIT - 1; bit >= 0; bit--) {
            // When analyze node p, make sure p != nullptr
            if (p->child[0] == nullptr) return res;
            if (p->child[0]->leaf < (1 << bit)) {
                p = p->child[0];
            } else {
                res = res | (1 << bit);
                if (p->child[1] == nullptr) return res; // make sure p != nullptr
                p = p->child[1];
            }
        }
        return res;
    }
private:
    Node* root;
    void insert_dfs(Node* root, int x, int bit) {
        root->cnt++;
        if (bit == -1) {
            root->leaf = 1;
            return;
        }
        int idx = (x >> bit) & 1;
        if (root->child[idx] == nullptr) root->child[idx] = new Node;
        insert_dfs(root->child[idx], x, bit - 1);
        root->leaf = 0;
        if (root->child[0]) root->leaf += root->child[0]->leaf;
        if (root->child[1]) root->leaf += root->child[1]->leaf;
    }
    void remove_dfs(Node* root, int x, int bit) {
        root->cnt--;
        if (bit == -1) {
            if (root->cnt == 0) root->leaf = 0;
            return;
        }
        int idx = (x >> bit) & 1;
        if (root->child[idx] != nullptr) remove_dfs(root->child[idx], x, bit - 1);
        root->leaf = 0;
        if (root->child[0]) root->leaf += root->child[0]->leaf;
        if (root->child[1]) root->leaf += root->child[1]->leaf;
    }
};
