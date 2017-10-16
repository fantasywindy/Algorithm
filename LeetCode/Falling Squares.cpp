#include <vector>
#include <iostream>
#include <set>

#include <map>
#include <unordered_map>
using namespace std;


class SegmentTree
{
public:
    void init(int n)
    {
        N = n;
        lazy.assign(4 * n, 0);
        trees.assign(4 * n, 0);
    }
    
    void update(int l, int r, int val)
    {
        int maxHeight = query(l, r);
        return update(1, val + maxHeight, l, r, 0, N);
    }
    
    int query(int l, int r)
    {
        return query(1, l, r, 0, N);
    }
    
private:
    
    void update(int id, int val, int x, int y, int l, int r)
    {
        if(lazy[id] != 0)
        {
            trees[id] = max(trees[id], lazy[id]);
            if(r - l >= 2)
            {
                lazy[id * 2] = lazy[id];
                lazy[id * 2 + 1] = lazy[id];
            }
            lazy[id] = 0;
        }
        
        if(x >= r || y <= l)
        {
            return;
        }
        
        if(l >= x && r <= y)
        {
            trees[id] = max(trees[id], val);
            
            if(r - l >= 2)
            {
                lazy[id * 2] = max(lazy[id * 2], val);
                lazy[id * 2 + 1] = max(lazy[id * 2 + 1], val);
            }
            
            
            return;
        }
        
        int mid = l + (r - l) / 2;
        update(id * 2, val, x, y, l, mid);
        update(id * 2 + 1, val, x, y, mid, r);
        trees[id] = max(trees[id * 2], trees[id * 2 + 1]);
    }
    
    
    int query(int id, int x, int y, int l, int r)
    {
        if(x >= r || y <= l)
        {
            return 0;
        }
        
        if(lazy[id] != 0)
        {
            trees[id] = max(trees[id], lazy[id]);
            if(r - l >= 2)
            {
                lazy[id * 2] = lazy[id];
                lazy[id * 2 + 1] = lazy[id];
            }
            lazy[id] = 0;
        }
        
        if(l >= x && r <= y)
        {
            return trees[id];
        }
        
        
        int mid = l + (r - l) / 2;
        
        return max( query(id * 2, x, y, l, mid), query(id * 2 + 1, x, y, mid, r));
        
        
    }
    
    
private:
    vector<int> trees;
    vector<int> lazy;
    int N;
};

class Solution {
public:
    vector<int> fallingSquares(vector<pair<int, int>>& positions) {
        int n = positions.size();
        
        set<int> t;
        
        for(auto item : positions)
        {
            int l = item.first;
            int r = item.first + item.second - 1;
            t.insert(l);
            t.insert(r);
        }
        
        
        unordered_map<int, int> posIndex;
        
        int index = 0;
        
        for(auto item : t)
        {
            posIndex[item] = index++;
        }
        
        
        SegmentTree T;
        T.init(index);
        
        vector<int> vec;
        
        for(auto p : positions)
        {
            int l = posIndex[p.first];
            int r = posIndex[p.first + p.second - 1] + 1;
            
            T.update(l, r, p.second);
            
            vec.push_back(T.query(0, index));
        }
        
        
        return vec;
    }
};

int main()
{
    Solution s;
    
    vector<pair<int, int> > pos = {{2,82},{57,22},{16,66},{46,15},{5,11},{9,83},{1,32},{87,91},{64,61},{87,53}};
    vector<int> ret = s.fallingSquares(pos);
    for(auto item : ret)
    {
        cout << item << endl;
    }
    return 0;
}
