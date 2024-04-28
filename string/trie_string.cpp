struct Trie {
    struct Node {
        Node* child[26];
        int cnt;
        Node() {
            for (int i = 0; i < 26; i++) child[i] = NULL;
            cnt = 0;
        }
    };

    Node* root;
    Trie() {
        root = new Node();
    }

    void insert(string &s) {
        Node* p = root;
        int idx;
        for (int i = 0; i < s.size(); i++) {
            idx = s[i] - 'a';
            if (p->child[idx] == NULL) p->child[idx] = new Node(); // each traversed edge represent a char of string
            p = p->child[idx]; // move to next node
        }
        p->cnt++;
    }

    bool find(string &s) {
        Node* p = root;
        int idx;
        for (int i = 0; i < s.size(); i++) {
            idx = s[i] - 'a';
            if (p->child[idx] == NULL) return false;
            p = p->child[idx];
        }
        return p->cnt > 0;
    }

    bool startWith(string &s) {
        Node* p = root;
        int idx;
        for (int i = 0; i < s.size(); i++) {
            idx = s[i] - 'a';
            if (p->child[idx] == NULL) return false;
            p = p->child[idx];
        }
        return true;
    }
    
    bool remove(string &s) {
        remove_internal(root, 0, s);
    }
    // recursive remove node: should delete current node?
    // this function should return true when the current node should be deleted from its parent => Use recursion to delete backtracking
    bool remove_internal(Node* p, int i, string &s) {
        if (p == NULL) return false;
        if (i == s.size()) {
            p->cnt--; // decrease word cnt
            return shouldDeleteCurrentNode(p); // no need to check deleting child in the current path because this is the last child
        }

        bool shouldDeleteChild = remove_internal(p->child[i], i + 1, s);
        if (shouldDeleteChild) {
            delete p->child[i];
            p->child[i] = NULL;
        }
        // only delete current node when:
        // + child is deleted
        // + node is empty (no child pointer is represented) 
        // + no word cnt
        if (shouldDeleteChild && shouldDeleteCurrentNode(p)) return true;
        return false;
    }
    // Should delete a node from its parent when:
    // cnt == 0 (no word end with this node)
    // no children pointer => No word is a prefix of path to this node
    bool shouldDeleteCurrentNode(Node* p) {
        for (int i = 0; i < p->child.size(); i++) {
            if (p->child[i] != NULL) return false;
        }
        return p->cnt == 0;
    }
};