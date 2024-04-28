struct Trie {
    struct Node {
        Node* child[2];
        int cnt;
        int val;
        Node() {
            for (int i = 0; i < 2; i++) child[i] = NULL;
            cnt = 0; val = -1;
        }
    };

    Node* root;
    Trie() {
        root = new Node();
    }

    void insert(int x) {
        Node* p = root;
        int idx;
        for (int i = 31; i >= 0; i--) {
            idx = (x >> i) & 1;
            if (p->child[idx] == NULL) p->child[idx] = new Node();
            p = p->child[idx];
        }
        p->cnt++;
        p->val = x;
    }

    int find_max(int x) {
        int x_bit, p_idx;
        Node* p = root;
        for (int i = 31; i >= 0; i--) {
            x_bit = (x >> i) & 1;
            if (x_bit) {
                if (p->child[0] != NULL) p_idx = 0;
                else p_idx = 1;
            } else {
                if (p->child[1] != NULL) p_idx = 1;
                else p_idx = 0;
            }
            p = p->child[p_idx];
        }
        return (x^(p->val));
    }
};
