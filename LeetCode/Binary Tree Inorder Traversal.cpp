/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if(root == nullptr)
        {
            return vector<int>();
        }
        
        stack<TreeNode *> stk;
        
        auto p = root;
        
        vector<int> ret;
        
        while(p || stk.empty() == false)
        {
            while(p)
            {
                stk.push(p);
                p = p->left;
            }
            
            //now p == nullptr;
            
            auto cur = stk.top();
            
            stk.pop();
            
            //cur must have no left, we can visit cur now
            ret.push_back(cur->val);
            
            //let's see if cur has right, if has go to right branch
            
            if(cur->right)
            {
                p = cur->right;
            }
        }
        
        return ret;
    }
};