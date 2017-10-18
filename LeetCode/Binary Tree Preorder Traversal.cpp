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
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode *> s;
        
        if(root == nullptr)
        {
            return vector<int>();
        }
        auto p = root;
        
        s.push(p);
        vector<int> ret;
        
        while(s.empty() == false)
        {
            //visited root first, then left and right;
            
            auto cur = s.top();
            
            ret.push_back(cur->val);
            
            s.pop();
            
            if(cur->right)
            {
                s.push(cur->right);
            }
            
            if(cur->left)
            {
                s.push(cur->left);
            }
            
        }
        
        return ret;
    }
};