/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        return check(p, q);
    }
    bool check(TreeNode* p, TreeNode* q)
    {
        bool current = true;

        if(p == NULL && q == NULL)
        {
            current = true;
        }
        else if(p == NULL || q == NULL)
        {
            current = false;
        }
        else
        {
            current = p->val == q->val;
            current = current && check(p->left, q->left);
            current = current && check(p->right, q->right);
        }
        return current;
    }
};