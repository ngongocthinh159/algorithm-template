bool isEmpty(Node* root) {
    for (int i = 0; i < 2; i++) if (root->child[i] != NULL) {
        return false;
    }
    return true;
}
// bool indicate that if the word is actually be decrease by 1 in the trie (remove 1 frequency from the trie)
// standing at a root, we only choose to either remove or not the child that get we to next character of the removed string
//      not remove the node itself
// a child node that get we to the next char can be remove only when:
//      + the removed word is decrease by 1 (isRemoved)
//      + the child node has not word (cnt = 0) and empty (all childs of child node are NULL)
bool remove(Node* root, int x, int depth) {
    if (depth == 31) {
        if (root->cnt > 0) {
            root->cnt--;
            return true;
        }
        return false;
    }

    int idx = ((x >> (30 - depth)) & 1);
    if (!root->child[idx]) return false;
    bool isRemoved = remove(root->child[idx], x, depth + 1);
    Node* tmp = root->child[idx];
    if (isRemoved && tmp->cnt == 0 && isEmpty(tmp)) {
        delete root->child[idx];
        root->child[idx] = NULL;
    }
    return isRemoved;
}
