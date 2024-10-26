#include <bits/stdc++.h>
using namespace std;

class Solution1 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        stack<TreeNode*> st;
        pushAllLeft(st, root);
        while (st.size()) {
           TreeNode* cur = st.top(); st.pop();
           res.push_back(cur->val);
           pushAllLeft(st, cur->right);
        }
        return res;
    }

    void pushAllLeft(stack<TreeNode*>& st, TreeNode* cur) {
        while (cur != NULL) {
            st.push(cur);
            cur = cur->left;
        }
    }
};

class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;

        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur != NULL || st.size()) {
            // Traverse left until can't, while traverse push node into stack
            while (cur != NULL) {
                st.push(cur);
                cur = cur->left;
            }

            // Pop node when can not traverse left anymore
            cur = st.top(); st.pop();
            res.push_back(cur->val);

            // Go to right of node when pop node done
            cur = cur->right;
        }

        return res;
    }
};

int main() {
    return 0;
}