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
    vector<int> postorderTraversal(TreeNode* root) {
        if(root == nullptr)
        {
            return ret;
        }
        
        auto p = root;
        
        TreeNode * pre = nullptr;
        
        stack<TreeNode *> stk;
        
        
        while(p || stk.empty() == false)
        {
            while(p)
            {
                stk.push(p);
                p = p->left;
            }
            
            //p is nullptr
            auto cur = stk.top();
            
            if(cur->right != nullptr && pre != cur->right)
            {
                p = cur->right;
            }
            else
            {
                visit(cur);
                stk.pop();
                pre = cur;
            }
        }
        
        return ret;
        
    }
    
    void visit(TreeNode * node)
    {
        ret.push_back(node->val);
    }
    
private:
    vector<int> ret;
};


class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if(root == nullptr)
        {
            return vector<int>();
        }
        stack<TreeNode *> s;
        TreeNode * pre = nullptr;
        s.push(root);
        vector<int> ret;
        while(s.empty() == false)
        {
            auto top = s.top();
            if(top->left == nullptr && top->right == nullptr)
            {
                ret.push_back(top->val);
                pre = top;
                s.pop();
            }
            else if(pre != nullptr && (top->left == pre || top->right == pre))
            {
                //all the children has been visited
                ret.push_back(top->val);
                pre = top;
                s.pop();
            }
            else
            {
                if(top->right != nullptr)
                {
                    s.push(top->right);
                }
                if(top->left != nullptr)
                {
                    s.push(top->left);
                }
            }
        }
        return ret;
    }
};